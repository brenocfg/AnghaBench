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
struct TYPE_5__ {int* unsigned_integer; } ;
struct TYPE_6__ {TYPE_1__ target; } ;
struct TYPE_7__ {TYPE_2__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */

__attribute__((used)) static int setting_uint_action_right_crt_switch_resolution_super(
      rarch_setting_t *setting, bool wraparound)
{
   if (!setting)
      return -1;

   switch (*setting->value.target.unsigned_integer)
   {
      case 0:
         *setting->value.target.unsigned_integer = 1;
         break;
      case 1: /* for dynamic super resolution switching - best fit */
         *setting->value.target.unsigned_integer = 1920;
         break;
      case 1920:
         *setting->value.target.unsigned_integer = 2560;
         break;
      case 2560:
         *setting->value.target.unsigned_integer = 3840;
         break;
      case 3840:
         *setting->value.target.unsigned_integer = 0;
         break;
   }

   return 0;
}