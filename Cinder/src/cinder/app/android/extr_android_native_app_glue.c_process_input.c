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
struct android_poll_source {int dummy; } ;
struct android_app {int /*<<< orphan*/  inputQueue; int /*<<< orphan*/  (* onInputEvent ) (struct android_app*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  AInputEvent ;

/* Variables and functions */
 int /*<<< orphan*/  AInputQueue_finishEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ AInputQueue_getEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ AInputQueue_preDispatchEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct android_app*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_input(struct android_app* app, struct android_poll_source* source) {
    AInputEvent* event = NULL;
    while (AInputQueue_getEvent(app->inputQueue, &event) >= 0) {
        //LOGV("New input event: type=%d\n", AInputEvent_getType(event));
        if (AInputQueue_preDispatchEvent(app->inputQueue, event)) {
            continue;
        }
        int32_t handled = 0;
        if (app->onInputEvent != NULL) handled = app->onInputEvent(app, event);
        AInputQueue_finishEvent(app->inputQueue, event, handled);
    }
}