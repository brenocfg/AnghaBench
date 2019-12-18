#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {int triggered; } ;
struct TYPE_7__ {int flags; TYPE_1__ cmd_trigger; int /*<<< orphan*/  (* change_handler ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ rarch_setting_t ;

/* Variables and functions */
 int SD_FLAG_EXIT ; 
 scalar_t__ setting_generic_action_ok_default (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int menu_setting_generic(rarch_setting_t *setting, bool wraparound)
{
   uint64_t flags = setting->flags;
   if (setting_generic_action_ok_default(setting, wraparound) != 0)
      return -1;

   if (setting->change_handler)
      setting->change_handler(setting);

   if ((flags & SD_FLAG_EXIT) && setting->cmd_trigger.triggered)
   {
      setting->cmd_trigger.triggered = false;
      return -1;
   }

   return 0;
}