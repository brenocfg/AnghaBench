#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ui_companion_toggle; scalar_t__ desktop_menu_enable; } ;
struct TYPE_7__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* toggle ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* toggle ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* init ) () ;} ;

/* Variables and functions */
 TYPE_2__* configuration_settings ; 
 int qt_is_inited ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* ui_companion ; 
 int /*<<< orphan*/  ui_companion_data ; 
 TYPE_3__ ui_companion_qt ; 
 int /*<<< orphan*/  ui_companion_qt_data ; 

void ui_companion_driver_toggle(bool force)
{
#ifdef HAVE_QT
   settings_t *settings = configuration_settings;
#endif

   if (ui_companion && ui_companion->toggle)
      ui_companion->toggle(ui_companion_data, false);

#ifdef HAVE_QT
   if (settings->bools.desktop_menu_enable)
   {
      if ((settings->bools.ui_companion_toggle || force) && !qt_is_inited)
      {
         ui_companion_qt_data = ui_companion_qt.init();
         qt_is_inited = true;
      }

      if (ui_companion_qt.toggle && qt_is_inited)
         ui_companion_qt.toggle(ui_companion_qt_data, force);
   }
#endif
}