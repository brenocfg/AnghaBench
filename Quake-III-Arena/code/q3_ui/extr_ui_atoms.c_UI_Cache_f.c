#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ArenaServers_Cache () ; 
 int /*<<< orphan*/  ConfirmMenu_Cache () ; 
 int /*<<< orphan*/  Controls_Cache () ; 
 int /*<<< orphan*/  Demos_Cache () ; 
 int /*<<< orphan*/  DriverInfo_Cache () ; 
 int /*<<< orphan*/  GraphicsOptions_Cache () ; 
 int /*<<< orphan*/  InGame_Cache () ; 
 int /*<<< orphan*/  MainMenu_Cache () ; 
 int /*<<< orphan*/  PlayerModel_Cache () ; 
 int /*<<< orphan*/  PlayerSettings_Cache () ; 
 int /*<<< orphan*/  Preferences_Cache () ; 
 int /*<<< orphan*/  ServerInfo_Cache () ; 
 int /*<<< orphan*/  ServerOptions_Cache () ; 
 int /*<<< orphan*/  SpecifyServer_Cache () ; 
 int /*<<< orphan*/  StartServer_Cache () ; 
 int /*<<< orphan*/  TeamMain_Cache () ; 
 int /*<<< orphan*/  UI_AddBots_Cache () ; 
 int /*<<< orphan*/  UI_BotSelectMenu_Cache () ; 
 int /*<<< orphan*/  UI_CDKeyMenu_Cache () ; 
 int /*<<< orphan*/  UI_CinematicsMenu_Cache () ; 
 int /*<<< orphan*/  UI_DisplayOptionsMenu_Cache () ; 
 int /*<<< orphan*/  UI_ModsMenu_Cache () ; 
 int /*<<< orphan*/  UI_NetworkOptionsMenu_Cache () ; 
 int /*<<< orphan*/  UI_RemoveBots_Cache () ; 
 int /*<<< orphan*/  UI_SPLevelMenu_Cache () ; 
 int /*<<< orphan*/  UI_SPPostgameMenu_Cache () ; 
 int /*<<< orphan*/  UI_SPSkillMenu_Cache () ; 
 int /*<<< orphan*/  UI_SetupMenu_Cache () ; 
 int /*<<< orphan*/  UI_SoundOptionsMenu_Cache () ; 

void UI_Cache_f( void ) {
	MainMenu_Cache();
	InGame_Cache();
	ConfirmMenu_Cache();
	PlayerModel_Cache();
	PlayerSettings_Cache();
	Controls_Cache();
	Demos_Cache();
	UI_CinematicsMenu_Cache();
	Preferences_Cache();
	ServerInfo_Cache();
	SpecifyServer_Cache();
	ArenaServers_Cache();
	StartServer_Cache();
	ServerOptions_Cache();
	DriverInfo_Cache();
	GraphicsOptions_Cache();
	UI_DisplayOptionsMenu_Cache();
	UI_SoundOptionsMenu_Cache();
	UI_NetworkOptionsMenu_Cache();
	UI_SPLevelMenu_Cache();
	UI_SPSkillMenu_Cache();
	UI_SPPostgameMenu_Cache();
	TeamMain_Cache();
	UI_AddBots_Cache();
	UI_RemoveBots_Cache();
	UI_SetupMenu_Cache();
//	UI_LoadConfig_Cache();
//	UI_SaveConfigMenu_Cache();
	UI_BotSelectMenu_Cache();
	UI_CDKeyMenu_Cache();
	UI_ModsMenu_Cache();

}