#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int jint ;
typedef  enum frontend_powerstate { ____Placeholder_frontend_powerstate } frontend_powerstate ;
struct TYPE_4__ {scalar_t__ getBatteryLevel; TYPE_1__* activity; scalar_t__ getPowerstate; } ;
struct TYPE_3__ {int /*<<< orphan*/  clazz; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_INT_METHOD (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int FRONTEND_POWERSTATE_NONE ; 
 scalar_t__ frontend_unix_powerstate_check_acpi (int*,int*,int*) ; 
 scalar_t__ frontend_unix_powerstate_check_acpi_sysfs (int*,int*,int*) ; 
 scalar_t__ frontend_unix_powerstate_check_apm (int*,int*,int*) ; 
 TYPE_2__* g_android ; 
 int /*<<< orphan*/ * jni_thread_getenv () ; 

__attribute__((used)) static enum frontend_powerstate frontend_unix_get_powerstate(
      int *seconds, int *percent)
{
   enum frontend_powerstate ret = FRONTEND_POWERSTATE_NONE;

#ifdef ANDROID
   jint powerstate = ret;
   jint battery_level = 0;
   JNIEnv *env = jni_thread_getenv();

   if (!env || !g_android)
      return ret;

   if (g_android->getPowerstate)
      CALL_INT_METHOD(env, powerstate,
            g_android->activity->clazz, g_android->getPowerstate);

   if (g_android->getBatteryLevel)
      CALL_INT_METHOD(env, battery_level,
            g_android->activity->clazz, g_android->getBatteryLevel);

   *percent = battery_level;

   ret = (enum frontend_powerstate)powerstate;
#else
   if (frontend_unix_powerstate_check_acpi_sysfs(&ret, seconds, percent))
      return ret;

   ret = FRONTEND_POWERSTATE_NONE;

   if (frontend_unix_powerstate_check_acpi(&ret, seconds, percent))
      return ret;

   if (frontend_unix_powerstate_check_apm(&ret, seconds, percent))
      return ret;
#endif

   return ret;
}