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
 scalar_t__* menuErrorMsg ; 
 int /*<<< orphan*/  menu_gfx_prepare () ; 
 int /*<<< orphan*/  menu_loop_root () ; 

void menu_loop(void)
{
	menu_gfx_prepare();

	menu_loop_root();

	menuErrorMsg[0] = 0;
}