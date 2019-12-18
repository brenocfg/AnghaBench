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
typedef  int /*<<< orphan*/  pa_mainloop ;
typedef  int /*<<< orphan*/  pa_context ;
typedef  enum pa_operation_state { ____Placeholder_pa_operation_state } pa_operation_state ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ PulseData ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int PA_OPERATION_DONE ; 
 int PA_OPERATION_RUNNING ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int ff_pulse_audio_connect_context (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_pulse_audio_disconnect_context (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * pa_context_get_sink_input_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pa_mainloop_iterate (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int pa_operation_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_get_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulse_audio_sink_input_cb ; 

__attribute__((used)) static int pulse_update_sink_input_info(AVFormatContext *h)
{
    PulseData *s = h->priv_data;
    pa_operation *op;
    enum pa_operation_state op_state;
    pa_mainloop *ml = NULL;
    pa_context *ctx = NULL;
    int ret = 0;

    if ((ret = ff_pulse_audio_connect_context(&ml, &ctx, s->server, "Update sink input information")) < 0)
        return ret;

    if (!(op = pa_context_get_sink_input_info(ctx, pa_stream_get_index(s->stream),
                                              pulse_audio_sink_input_cb, h))) {
        ret = AVERROR_EXTERNAL;
        goto fail;
    }

    while ((op_state = pa_operation_get_state(op)) == PA_OPERATION_RUNNING)
        pa_mainloop_iterate(ml, 1, NULL);
    pa_operation_unref(op);
    if (op_state != PA_OPERATION_DONE) {
        ret = AVERROR_EXTERNAL;
        goto fail;
    }

  fail:
    ff_pulse_audio_disconnect_context(&ml, &ctx);
    if (ret)
        av_log(s, AV_LOG_ERROR, "pa_context_get_sink_input_info failed.\n");
    return ret;
}