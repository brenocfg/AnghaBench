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
 int /*<<< orphan*/ * Display_CaptureItem (int,int) ; 
 int /*<<< orphan*/ * Menu_GetFocused () ; 
 int /*<<< orphan*/  Menu_HandleKey (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void Display_HandleKey(int key, qboolean down, int x, int y) {
	menuDef_t *menu = Display_CaptureItem(x, y);
	if (menu == NULL) {  
		menu = Menu_GetFocused();
	}
	if (menu) {
		Menu_HandleKey(menu, key, down );
	}
}