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
 int PBTN_DOWN ; 
 int PBTN_L ; 
 int PBTN_LEFT ; 
 int PBTN_MBACK ; 
 int PBTN_MOK ; 
 int PBTN_R ; 
 int PBTN_RIGHT ; 
 int PBTN_UP ; 
 int PicoPatchCount ; 
 TYPE_1__* PicoPatches ; 
 int /*<<< orphan*/  draw_patchlist (int) ; 
 int in_menu_wait (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void menu_loop_patches(void)
{
	static int menu_sel = 0;
	int inp;

	for (;;)
	{
		draw_patchlist(menu_sel);
		inp = in_menu_wait(PBTN_UP|PBTN_DOWN|PBTN_LEFT|PBTN_RIGHT|PBTN_L|PBTN_R
				|PBTN_MOK|PBTN_MBACK, NULL, 33);
		if (inp & PBTN_UP  ) { menu_sel--; if (menu_sel < 0) menu_sel = PicoPatchCount; }
		if (inp & PBTN_DOWN) { menu_sel++; if (menu_sel > PicoPatchCount) menu_sel = 0; }
		if (inp &(PBTN_LEFT|PBTN_L))  { menu_sel-=10; if (menu_sel < 0) menu_sel = 0; }
		if (inp &(PBTN_RIGHT|PBTN_R)) { menu_sel+=10; if (menu_sel > PicoPatchCount) menu_sel = PicoPatchCount; }
		if (inp & PBTN_MOK) { // action
			if (menu_sel < PicoPatchCount)
				PicoPatches[menu_sel].active = !PicoPatches[menu_sel].active;
			else 	break;
		}
		if (inp & PBTN_MBACK)
			break;
	}
}