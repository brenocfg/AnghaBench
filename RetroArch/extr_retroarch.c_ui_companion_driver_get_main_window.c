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
struct TYPE_3__ {void* (* get_main_window ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ui_companion_driver_t ;

/* Variables and functions */
 void* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* ui_companion ; 
 int /*<<< orphan*/  ui_companion_data ; 

void *ui_companion_driver_get_main_window(void)
{
   const ui_companion_driver_t *ui = ui_companion;
   if (!ui || !ui->get_main_window)
      return NULL;
   return ui->get_main_window(ui_companion_data);
}