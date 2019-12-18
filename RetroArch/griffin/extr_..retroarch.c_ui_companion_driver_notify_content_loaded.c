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
struct TYPE_3__ {int /*<<< orphan*/  (* notify_content_loaded ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ui_companion_driver_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* ui_companion ; 
 int /*<<< orphan*/  ui_companion_data ; 

void ui_companion_driver_notify_content_loaded(void)
{
   const ui_companion_driver_t *ui = ui_companion;
   if (ui && ui->notify_content_loaded)
      ui->notify_content_loaded(ui_companion_data);
}