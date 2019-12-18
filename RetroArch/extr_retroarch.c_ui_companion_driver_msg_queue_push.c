#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* msg_queue_push ) (int /*<<< orphan*/ ,char const*,unsigned int,unsigned int,int) ;} ;
typedef  TYPE_2__ ui_companion_driver_t ;
struct TYPE_7__ {scalar_t__ desktop_menu_enable; } ;
struct TYPE_9__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* msg_queue_push ) (int /*<<< orphan*/ ,char const*,unsigned int,unsigned int,int) ;} ;

/* Variables and functions */
 TYPE_3__* configuration_settings ; 
 scalar_t__ qt_is_inited ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const*,unsigned int,unsigned int,int) ; 
 TYPE_2__* ui_companion ; 
 int /*<<< orphan*/  ui_companion_data ; 
 TYPE_4__ ui_companion_qt ; 
 int /*<<< orphan*/  ui_companion_qt_data ; 

__attribute__((used)) static void ui_companion_driver_msg_queue_push(
      const char *msg, unsigned priority, unsigned duration, bool flush)
{
   const ui_companion_driver_t *ui = ui_companion;

   if (ui && ui->msg_queue_push)
      ui->msg_queue_push(ui_companion_data, msg, priority, duration, flush);
#ifdef HAVE_QT
   {
      settings_t *settings            = configuration_settings;
      if (settings->bools.desktop_menu_enable)
         if (ui_companion_qt.msg_queue_push && qt_is_inited)
            ui_companion_qt.msg_queue_push(ui_companion_qt_data, msg, priority, duration, flush);
   }
#endif
}