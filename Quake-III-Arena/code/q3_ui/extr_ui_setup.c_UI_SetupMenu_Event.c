#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int id; } ;
typedef  TYPE_1__ menucommon_s ;

/* Variables and functions */
#define  ID_BACK 134 
#define  ID_CDKEY 133 
#define  ID_CUSTOMIZECONTROLS 132 
#define  ID_CUSTOMIZEPLAYER 131 
#define  ID_DEFAULTS 130 
#define  ID_GAME 129 
#define  ID_SYSTEMCONFIG 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  Setup_ResetDefaults_Action ; 
 int /*<<< orphan*/  Setup_ResetDefaults_Draw ; 
 int /*<<< orphan*/  UI_CDKeyMenu () ; 
 int /*<<< orphan*/  UI_ConfirmMenu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_ControlsMenu () ; 
 int /*<<< orphan*/  UI_GraphicsOptionsMenu () ; 
 int /*<<< orphan*/  UI_PlayerSettingsMenu () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_PreferencesMenu () ; 

__attribute__((used)) static void UI_SetupMenu_Event( void *ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_CUSTOMIZEPLAYER:
		UI_PlayerSettingsMenu();
		break;

	case ID_CUSTOMIZECONTROLS:
		UI_ControlsMenu();
		break;

	case ID_SYSTEMCONFIG:
		UI_GraphicsOptionsMenu();
		break;

	case ID_GAME:
		UI_PreferencesMenu();
		break;

	case ID_CDKEY:
		UI_CDKeyMenu();
		break;

//	case ID_LOAD:
//		UI_LoadConfigMenu();
//		break;

//	case ID_SAVE:
//		UI_SaveConfigMenu();
//		break;

	case ID_DEFAULTS:
		UI_ConfirmMenu( "SET TO DEFAULTS?", Setup_ResetDefaults_Draw, Setup_ResetDefaults_Action );
		break;

	case ID_BACK:
		UI_PopMenu();
		break;
	}
}