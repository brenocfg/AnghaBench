#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ menu_navigation_wraparound_enable; } ;
struct TYPE_14__ {TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_12__ {int /*<<< orphan*/  string; } ;
struct TYPE_13__ {TYPE_2__ target; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* change_handler ) (TYPE_5__*) ;int /*<<< orphan*/  size; TYPE_3__ value; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ rarch_setting_t ;
struct TYPE_16__ {int /*<<< orphan*/  len; int /*<<< orphan*/  s; int /*<<< orphan*/  label; } ;
typedef  TYPE_6__ driver_ctx_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_DRIVER_CTL_FIND_LAST ; 
 int /*<<< orphan*/  RARCH_DRIVER_CTL_FIND_PREV ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  driver_ctl (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static int setting_string_action_left_driver(rarch_setting_t *setting,
      bool wraparound)
{
   driver_ctx_info_t drv;

   if (!setting)
      return -1;

   drv.label = setting->name;
   drv.s     = setting->value.target.string;
   drv.len   = setting->size;

   if (!driver_ctl(RARCH_DRIVER_CTL_FIND_PREV, &drv))
   {
      settings_t *settings = config_get_ptr();

      if (settings && settings->bools.menu_navigation_wraparound_enable)
      {
         drv.label = setting->name;
         drv.s     = setting->value.target.string;
         drv.len   = setting->size;
         driver_ctl(RARCH_DRIVER_CTL_FIND_LAST, &drv);
      }
   }

   if (setting->change_handler)
      setting->change_handler(setting);

   return 0;
}