#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct android_app {TYPE_1__* activity; } ;
struct TYPE_5__ {int /*<<< orphan*/  onLocationFree; } ;
typedef  TYPE_2__ androidlocation_t ;
struct TYPE_4__ {int /*<<< orphan*/  clazz; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_VOID_METHOD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ g_android ; 
 int /*<<< orphan*/ * jni_thread_getenv () ; 

__attribute__((used)) static void android_location_free(void *data)
{
   struct android_app *android_app = (struct android_app*)g_android;
   androidlocation_t *androidlocation = (androidlocation_t*)data;
   JNIEnv *env = jni_thread_getenv();
   if (!env)
      return;

   CALL_VOID_METHOD(env, android_app->activity->clazz,
         androidlocation->onLocationFree);

   free(androidlocation);
}