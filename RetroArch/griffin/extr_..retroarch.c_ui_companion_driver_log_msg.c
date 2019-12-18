#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ desktop_menu_enable; } ;
struct TYPE_6__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* log_msg ) (scalar_t__,char const*) ;} ;

/* Variables and functions */
 TYPE_2__* configuration_settings ; 
 scalar_t__ qt_is_inited ; 
 int /*<<< orphan*/  stub1 (scalar_t__,char const*) ; 
 TYPE_3__ ui_companion_qt ; 
 scalar_t__ ui_companion_qt_data ; 

void ui_companion_driver_log_msg(const char *msg)
{
#ifdef HAVE_QT
   settings_t *settings = configuration_settings;

   if (settings->bools.desktop_menu_enable)
      if (ui_companion_qt_data && qt_is_inited)
         ui_companion_qt.log_msg(ui_companion_qt_data, msg);
#endif
}