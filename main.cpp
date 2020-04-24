#include <dllentry.h>
#include <log.h>
#include "settings.h"
//#include "playerdb.h"
#include <command.h>
#include <Command/Command.h>
#include <Command/CommandRegistry.h>
#include <Command/CommandPermissionLevel.h>
#include <Command/CommandFlag.h>
#include <Command/CommandParameterData.h>
#include <Command/CommandOutput.h>
#include <Command/CommandOrigin.h>

DEF_LOGGER("EZMod1");
DEFAULT_SETTINGS(settings);

// PS: Reserved for compatibility purposes
// If it is not necessary, keep both functions empty
// Initialization can be done in the PreInit function
// Incorrect use of this function may cause a crash
void dllenter() {}
void dllexit() {}

void PreInit() {
  LOGV("pre init");
  // You can use the event system to receive and process events
  // The following is an example
//  Mod::PlayerDatabase::GetInstance().AddListener(SIG("joined"), [](Mod::PlayerEntry const &entry) {
//    LOGV("joined name: %s, xuid: %d") % entry.name % entry.xuid;
//  });
//  Mod::PlayerDatabase::GetInstance().AddListener(
//      SIG("left"), [](Mod::PlayerEntry const &entry) { LOGV("left name: %s, xuid: %d") % entry.name % entry.xuid; });
}

class HelloWorldCommand : public Command {
public:
  HelloWorldCommand() {}

  void execute(CommandOrigin const &origin, CommandOutput &output) { output.success("Hello world!"); }
  static void setup(CommandRegistry *registry) {
    registry->registerCommand(
        "helloworld", "My first command", CommandPermissionLevel::Any, CommandFlagCheat, CommandFlagNone);
    registry->registerOverload<HelloWorldCommand>("helloworld");
  }
};

void PostInit() {
  LOGV("post init");
  Mod::CommandSupport::GetInstance().AddListener(SIG("loaded"), &HelloWorldCommand::setup);
}

void ServerStart() { LOGV("server start"); }