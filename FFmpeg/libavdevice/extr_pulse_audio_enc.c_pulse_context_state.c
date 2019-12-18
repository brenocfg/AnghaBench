#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_context ;
struct TYPE_2__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ PulseData ;

/* Variables and functions */
#define  PA_CONTEXT_FAILED 130 
#define  PA_CONTEXT_READY 129 
#define  PA_CONTEXT_TERMINATED 128 
 int pa_context_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulse_context_state(pa_context *ctx, void *userdata)
{
    PulseData *s = userdata;

    if (s->ctx != ctx)
        return;

    switch (pa_context_get_state(ctx)) {
        case PA_CONTEXT_READY:
        case PA_CONTEXT_FAILED:
        case PA_CONTEXT_TERMINATED:
            pa_threaded_mainloop_signal(s->mainloop, 0);
        default:
            break;
    }
}