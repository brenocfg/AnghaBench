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
struct TYPE_2__ {int active; } ;

/* Variables and functions */
 unsigned long PBTN_CIRCLE ; 
 unsigned long PBTN_DOWN ; 
 unsigned long PBTN_L ; 
 unsigned long PBTN_LEFT ; 
 unsigned long PBTN_R ; 
 unsigned long PBTN_RIGHT ; 
 unsigned long PBTN_UP ; 
 unsigned long PBTN_X ; 
 int PicoPatchCount ; 
 TYPE_1__* PicoPatches ; 
 int /*<<< orphan*/  draw_patchlist (int) ; 
 unsigned long in_menu_wait (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void patches_menu_loop(void)
{
	int menu_sel = 0;
	unsigned long inp = 0;

	for(;;)
	{
		draw_patchlist(menu_sel);
		inp = in_menu_wait(PBTN_UP|PBTN_DOWN|PBTN_LEFT|PBTN_RIGHT|PBTN_L|PBTN_R|PBTN_X|PBTN_CIRCLE, 0);
		if(inp & PBTN_UP  ) { menu_sel--; if (menu_sel < 0) menu_sel = PicoPatchCount; }
		if(inp & PBTN_DOWN) { menu_sel++; if (menu_sel > PicoPatchCount) menu_sel = 0; }
		if(inp &(PBTN_LEFT|PBTN_L))  { menu_sel-=10; if (menu_sel < 0) menu_sel = 0; }
		if(inp &(PBTN_RIGHT|PBTN_R)) { menu_sel+=10; if (menu_sel > PicoPatchCount) menu_sel = PicoPatchCount; }
		if(inp & PBTN_CIRCLE) { // action
			if (menu_sel < PicoPatchCount)
				PicoPatches[menu_sel].active = !PicoPatches[menu_sel].active;
			else 	return;
		}
		if(inp & PBTN_X) return;
	}

}