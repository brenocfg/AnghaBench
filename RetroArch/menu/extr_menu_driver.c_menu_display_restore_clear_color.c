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
struct TYPE_2__ {int /*<<< orphan*/  (* restore_clear_color ) () ;} ;

/* Variables and functions */
 TYPE_1__* menu_disp ; 
 int /*<<< orphan*/  stub1 () ; 

bool menu_display_restore_clear_color(void)
{
   if (!menu_disp || !menu_disp->restore_clear_color)
      return false;
   menu_disp->restore_clear_color();
   return true;
}