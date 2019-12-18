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
 int /*<<< orphan*/  e_menu_cd_options ; 
 int /*<<< orphan*/  me_loop (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int menu_loop_cd_options(int id, int keys)
{
	static int sel = 0;
	me_loop(e_menu_cd_options, &sel);
	return 0;
}