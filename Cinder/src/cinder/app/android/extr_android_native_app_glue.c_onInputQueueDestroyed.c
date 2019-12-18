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
typedef  TYPE_1__ ANativeActivity ;
typedef  int /*<<< orphan*/  AInputQueue ;

/* Variables and functions */
 int /*<<< orphan*/  LOGV (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  android_app_set_input (struct android_app*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
    LOGV("InputQueueDestroyed: %p -- %p\n", activity, queue);
    android_app_set_input((struct android_app*)activity->instance, NULL);
}