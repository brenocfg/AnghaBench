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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_crt_switch_resolution_super(
      rarch_setting_t *setting,
      char *s, size_t len)
{
   if (!setting)
      return;

   if (*setting->value.target.unsigned_integer == 0)
      strlcpy(s, "NATIVE", len);
   else if (*setting->value.target.unsigned_integer == 1)
      strlcpy(s, "DYNAMIC", len);
   else
      snprintf(s, len, "%d", *setting->value.target.unsigned_integer); 
}