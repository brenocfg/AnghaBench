#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct android_app {int dummy; } ;
struct TYPE_4__ {scalar_t__ instance; } ;
typedef  int /*<<< orphan*/  ANativeWindow ;
typedef  TYPE_1__ ANativeActivity ;

/* Variables and functions */
 int /*<<< orphan*/  LOGV (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  android_app_set_window (struct android_app*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
    LOGV("NativeWindowDestroyed: %p -- %p\n", activity, window);
    android_app_set_window((struct android_app*)activity->instance, NULL);
}