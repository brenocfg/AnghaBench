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
struct TYPE_8__ {int /*<<< orphan*/  (* notify_refresh ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ ui_companion_driver_t ;
struct TYPE_7__ {scalar_t__ desktop_menu_enable; } ;
struct TYPE_9__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* notify_refresh ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__* configuration_settings ; 
 scalar_t__ qt_is_inited ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 TYPE_2__* ui_companion ; 
 int /*<<< orphan*/  ui_companion_data ; 
 TYPE_4__ ui_companion_qt ; 
 int /*<<< orphan*/  ui_companion_qt_data ; 

void ui_companion_driver_notify_refresh(void)
{
   const ui_companion_driver_t *ui = ui_companion;
#ifdef HAVE_QT
   settings_t      *settings       = configuration_settings;
#endif

   if (!ui)
      return;
   if (ui->notify_refresh)
      ui->notify_refresh(ui_companion_data);
#ifdef HAVE_QT
   if (settings->bools.desktop_menu_enable)
      if (ui_companion_qt.notify_refresh && qt_is_inited)
         ui_companion_qt.notify_refresh(ui_companion_qt_data);
#endif
}