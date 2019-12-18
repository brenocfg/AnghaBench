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
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  menuDef_t ;

/* Variables and functions */
 int KEYCATCH_UI ; 
 int K_ESCAPE ; 
 scalar_t__ Menu_Count () ; 
 int /*<<< orphan*/ * Menu_GetFocused () ; 
 int /*<<< orphan*/  Menu_HandleKey (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Menus_AnyFullScreenVisible () ; 
 int /*<<< orphan*/  Menus_CloseAll () ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Key_ClearStates () ; 
 int trap_Key_GetCatcher () ; 
 int /*<<< orphan*/  trap_Key_SetCatcher (int) ; 

void _UI_KeyEvent( int key, qboolean down ) {

  if (Menu_Count() > 0) {
    menuDef_t *menu = Menu_GetFocused();
		if (menu) {
			if (key == K_ESCAPE && down && !Menus_AnyFullScreenVisible()) {
				Menus_CloseAll();
			} else {
				Menu_HandleKey(menu, key, down );
			}
		} else {
			trap_Key_SetCatcher( trap_Key_GetCatcher() & ~KEYCATCH_UI );
			trap_Key_ClearStates();
			trap_Cvar_Set( "cl_paused", "0" );
		}
  }

  //if ((s > 0) && (s != menu_null_sound)) {
	//  trap_S_StartLocalSound( s, CHAN_LOCAL_SOUND );
  //}
}