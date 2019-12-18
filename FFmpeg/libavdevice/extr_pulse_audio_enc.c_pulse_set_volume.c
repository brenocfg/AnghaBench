#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_volume_t ;
struct TYPE_7__ {int /*<<< orphan*/  channels; } ;
typedef  TYPE_1__ pa_sample_spec ;
typedef  int /*<<< orphan*/  pa_operation ;
typedef  int /*<<< orphan*/  pa_cvolume ;
struct TYPE_8__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  ctx; int /*<<< orphan*/  mainloop; int /*<<< orphan*/  base_volume; } ;
typedef  TYPE_2__ PulseData ;

/* Variables and functions */
 double PA_VOLUME_NORM ; 
 int /*<<< orphan*/  lrint (double) ; 
 int /*<<< orphan*/ * pa_context_set_sink_input_volume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pa_cvolume_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  pa_stream_get_index (int /*<<< orphan*/ ) ; 
 TYPE_1__* pa_stream_get_sample_spec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_sw_cvolume_multiply_scalar (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_sw_volume_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulse_context_result ; 
 int pulse_finish_context_operation (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int pulse_set_volume(PulseData *s, double volume)
{
    pa_operation *op;
    pa_cvolume cvol;
    pa_volume_t vol;
    const pa_sample_spec *ss = pa_stream_get_sample_spec(s->stream);

    vol = pa_sw_volume_multiply(lrint(volume * PA_VOLUME_NORM), s->base_volume);
    pa_cvolume_set(&cvol, ss->channels, PA_VOLUME_NORM);
    pa_sw_cvolume_multiply_scalar(&cvol, &cvol, vol);
    pa_threaded_mainloop_lock(s->mainloop);
    op = pa_context_set_sink_input_volume(s->ctx, pa_stream_get_index(s->stream),
                                          &cvol, pulse_context_result, s);
    return pulse_finish_context_operation(s, op, "pa_context_set_sink_input_volume");
}