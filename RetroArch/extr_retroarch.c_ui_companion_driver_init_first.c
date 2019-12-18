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
struct TYPE_8__ {int /*<<< orphan*/  (* init ) () ;} ;
typedef  TYPE_2__ ui_companion_driver_t ;
struct TYPE_7__ {scalar_t__ ui_companion_start_on_boot; scalar_t__ ui_companion_toggle; scalar_t__ desktop_menu_enable; } ;
struct TYPE_9__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* init ) () ;} ;

/* Variables and functions */
 TYPE_3__* configuration_settings ; 
 int qt_is_inited ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 TYPE_2__* ui_companion ; 
 int /*<<< orphan*/  ui_companion_data ; 
 int /*<<< orphan*/  ui_companion_driver_toggle (int) ; 
 scalar_t__* ui_companion_drivers ; 
 TYPE_4__ ui_companion_qt ; 
 int /*<<< orphan*/  ui_companion_qt_data ; 

void ui_companion_driver_init_first(void)
{
   settings_t *settings       = configuration_settings;

   ui_companion               = (ui_companion_driver_t*)ui_companion_drivers[0];

#ifdef HAVE_QT
   if (settings->bools.desktop_menu_enable && settings->bools.ui_companion_toggle)
   {
      ui_companion_qt_data = ui_companion_qt.init();
      qt_is_inited = true;
   }
#endif

   if (ui_companion)
   {
      if (settings->bools.ui_companion_start_on_boot)
      {
         if (ui_companion->init)
            ui_companion_data = ui_companion->init();

         ui_companion_driver_toggle(false);
      }
   }
}