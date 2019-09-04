#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  base_volume; } ;
typedef  TYPE_1__ pa_sink_info ;
typedef  int /*<<< orphan*/  pa_context ;
struct TYPE_6__ {int /*<<< orphan*/  base_volume; int /*<<< orphan*/  mainloop; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_2__ PulseData ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int PA_SINK_FLAT_VOLUME ; 
 int /*<<< orphan*/  PA_VOLUME_NORM ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulse_audio_sink_device_cb(pa_context *ctx, const pa_sink_info *dev,
                                       int eol, void *userdata)
{
    PulseData *s = userdata;

    if (s->ctx != ctx)
        return;

    if (eol) {
        pa_threaded_mainloop_signal(s->mainloop, 0);
    } else {
        if (dev->flags & PA_SINK_FLAT_VOLUME)
            s->base_volume = dev->base_volume;
        else
            s->base_volume = PA_VOLUME_NORM;
        av_log(s, AV_LOG_DEBUG, "base volume: %u\n", s->base_volume);
    }
}