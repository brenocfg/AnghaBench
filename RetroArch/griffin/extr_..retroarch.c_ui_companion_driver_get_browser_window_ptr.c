#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  const* browser_window; } ;
typedef  TYPE_1__ ui_companion_driver_t ;
typedef  int /*<<< orphan*/  ui_browser_window_t ;

/* Variables and functions */
 TYPE_1__* ui_companion ; 

const ui_browser_window_t *ui_companion_driver_get_browser_window_ptr(void)
{
   const ui_companion_driver_t *ui = ui_companion;
   if (!ui)
      return NULL;
   return ui->browser_window;
}