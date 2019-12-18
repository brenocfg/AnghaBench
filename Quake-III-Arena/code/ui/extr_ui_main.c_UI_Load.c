#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ name; } ;
struct TYPE_5__ {TYPE_1__ window; } ;
typedef  TYPE_2__ menuDef_t ;

/* Variables and functions */
 TYPE_2__* Menu_GetFocused () ; 
 int /*<<< orphan*/  Menus_ActivateByName (char*) ; 
 int /*<<< orphan*/  Menus_CloseAll () ; 
 int /*<<< orphan*/  String_Init () ; 
 char* UI_Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  UI_LoadArenas () ; 
 int /*<<< orphan*/  UI_LoadMenus (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_ParseGameInfo (char*) ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strcpy (char*,scalar_t__) ; 

void UI_Load() {
	char lastName[1024];
  menuDef_t *menu = Menu_GetFocused();
	char *menuSet = UI_Cvar_VariableString("ui_menuFiles");
	if (menu && menu->window.name) {
		strcpy(lastName, menu->window.name);
	}
	if (menuSet == NULL || menuSet[0] == '\0') {
		menuSet = "ui/menus.txt";
	}

	String_Init();

#ifdef PRE_RELEASE_TADEMO
	UI_ParseGameInfo("demogameinfo.txt");
#else
	UI_ParseGameInfo("gameinfo.txt");
	UI_LoadArenas();
#endif

	UI_LoadMenus(menuSet, qtrue);
	Menus_CloseAll();
	Menus_ActivateByName(lastName);

}