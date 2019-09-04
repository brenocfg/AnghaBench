#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_operation ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  mainloop; } ;
typedef  TYPE_1__ PulseData ;

/* Variables and functions */
 int /*<<< orphan*/  PA_SUBSCRIPTION_MASK_SINK_INPUT ; 
 int /*<<< orphan*/ * pa_context_subscribe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulse_context_result ; 
 int pulse_finish_context_operation (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int pulse_subscribe_events(PulseData *s)
{
    pa_operation *op;

    pa_threaded_mainloop_lock(s->mainloop);
    op = pa_context_subscribe(s->ctx, PA_SUBSCRIPTION_MASK_SINK_INPUT, pulse_context_result, s);
    return pulse_finish_context_operation(s, op, "pa_context_subscribe");
}