#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  device_model ;

/* Variables and functions */
 int PROP_VALUE_MAX ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 scalar_t__ device_is_xperia_play (char*) ; 
 int /*<<< orphan*/  frontend_android_get_name (char*,int) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int frontend_unix_get_rating(void)
{
#ifdef ANDROID
   char device_model[PROP_VALUE_MAX] = {0};
   frontend_android_get_name(device_model, sizeof(device_model));

   RARCH_LOG("ro.product.model: (%s).\n", device_model);

   if (device_is_xperia_play(device_model))
      return 6;
   else if (strstr(device_model, "GT-I9505"))
      return 12;
   else if (strstr(device_model, "SHIELD"))
      return 13;
#endif
   return -1;
}