#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* boolean; } ;
struct TYPE_7__ {TYPE_1__ target; } ;
struct TYPE_8__ {TYPE_2__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  setting_set_with_string_representation (TYPE_3__*,char*) ; 

__attribute__((used)) static int setting_bool_action_ok_default(rarch_setting_t *setting, bool wraparound)
{
   if (!setting)
      return -1;

   (void)wraparound; /* TODO/FIXME - handle this */

   setting_set_with_string_representation(setting,
         *setting->value.target.boolean ? "false" : "true");

   return 0;
}