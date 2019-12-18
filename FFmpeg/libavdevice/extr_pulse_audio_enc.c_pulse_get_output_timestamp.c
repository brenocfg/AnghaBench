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
typedef  scalar_t__ pa_usec_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__ timestamp; int /*<<< orphan*/  mainloop; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ PulseData ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ av_gettime () ; 
 int /*<<< orphan*/  pa_stream_get_latency (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulse_get_output_timestamp(AVFormatContext *h, int stream, int64_t *dts, int64_t *wall)
{
    PulseData *s = h->priv_data;
    pa_usec_t latency;
    int neg;
    pa_threaded_mainloop_lock(s->mainloop);
    pa_stream_get_latency(s->stream, &latency, &neg);
    pa_threaded_mainloop_unlock(s->mainloop);
    if (wall)
        *wall = av_gettime();
    if (dts)
        *dts = s->timestamp - (neg ? -latency : latency);
}