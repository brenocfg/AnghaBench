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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int pa_subscription_event_type_t ;
typedef  int /*<<< orphan*/  pa_context ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ PulseData ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int PA_SUBSCRIPTION_EVENT_CHANGE ; 
 int PA_SUBSCRIPTION_EVENT_FACILITY_MASK ; 
 int PA_SUBSCRIPTION_EVENT_SINK_INPUT ; 
 int PA_SUBSCRIPTION_EVENT_TYPE_MASK ; 
 int /*<<< orphan*/  pulse_update_sink_input_info (TYPE_2__*) ; 

__attribute__((used)) static void pulse_event(pa_context *ctx, pa_subscription_event_type_t t,
                        uint32_t idx, void *userdata)
{
    AVFormatContext *h = userdata;
    PulseData *s = h->priv_data;

    if (s->ctx != ctx)
        return;

    if ((t & PA_SUBSCRIPTION_EVENT_FACILITY_MASK) == PA_SUBSCRIPTION_EVENT_SINK_INPUT) {
        if ((t & PA_SUBSCRIPTION_EVENT_TYPE_MASK) == PA_SUBSCRIPTION_EVENT_CHANGE)
            // Calling from mainloop callback. No need to lock mainloop.
            pulse_update_sink_input_info(h);
    }
}