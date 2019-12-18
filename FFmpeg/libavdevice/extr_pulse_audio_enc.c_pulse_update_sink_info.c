#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_operation ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  device; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ PulseData ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ PA_OPERATION_RUNNING ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pa_context_get_sink_info_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ pa_operation_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulse_audio_sink_device_cb ; 

__attribute__((used)) static int pulse_update_sink_info(AVFormatContext *h)
{
    PulseData *s = h->priv_data;
    pa_operation *op;
    if (!(op = pa_context_get_sink_info_by_name(s->ctx, s->device,
                                                pulse_audio_sink_device_cb, s))) {
        av_log(s, AV_LOG_ERROR, "pa_context_get_sink_info_by_name failed.\n");
        return AVERROR_EXTERNAL;
    }
    while (pa_operation_get_state(op) == PA_OPERATION_RUNNING)
        pa_threaded_mainloop_wait(s->mainloop);
    pa_operation_unref(op);
    return 0;
}