#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* event_command ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ ui_companion_driver_t ;
typedef  enum event_command { ____Placeholder_event_command } event_command ;
struct TYPE_5__ {int /*<<< orphan*/  (* event_command ) (int /*<<< orphan*/ ,int) ;scalar_t__ toggle; } ;

/* Variables and functions */
 scalar_t__ qt_is_inited ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ui_companion ; 
 int /*<<< orphan*/  ui_companion_data ; 
 TYPE_2__ ui_companion_qt ; 
 int /*<<< orphan*/  ui_companion_qt_data ; 

void ui_companion_event_command(enum event_command action)
{
   const ui_companion_driver_t *ui = ui_companion;

   if (ui && ui->event_command)
      ui->event_command(ui_companion_data, action);
#ifdef HAVE_QT
   if (ui_companion_qt.toggle && qt_is_inited)
      ui_companion_qt.event_command(ui_companion_qt_data, action);
#endif
}