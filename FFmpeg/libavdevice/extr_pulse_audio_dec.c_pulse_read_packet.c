#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pa_usec_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_11__ {scalar_t__ audio_codec_id; TYPE_1__* priv_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  pts; } ;
struct TYPE_9__ {int channels; int last_period; int /*<<< orphan*/  mainloop; int /*<<< orphan*/  stream; int /*<<< orphan*/  timefilter; scalar_t__ wallclock; } ;
typedef  TYPE_1__ PulseData ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  CHECK_DEAD_GOTO (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_SUCCESS_GOTO (int,int,int /*<<< orphan*/ ) ; 
 int DEFAULT_CODEC_ID ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_get_bits_per_sample (int) ; 
 int /*<<< orphan*/  av_gettime () ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_new_packet (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  ff_timefilter_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ ) ; 
 int pa_stream_drop (int /*<<< orphan*/ ) ; 
 scalar_t__ pa_stream_get_latency (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int pa_stream_peek (int /*<<< orphan*/ ,void const**,size_t*) ; 
 int /*<<< orphan*/  pa_stream_update_timing_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_and_fail ; 

__attribute__((used)) static int pulse_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    PulseData *pd  = s->priv_data;
    int ret;
    size_t read_length;
    const void *read_data = NULL;
    int64_t dts;
    pa_usec_t latency;
    int negative;

    pa_threaded_mainloop_lock(pd->mainloop);

    CHECK_DEAD_GOTO(pd, ret, unlock_and_fail);

    while (!read_data) {
        int r;

        r = pa_stream_peek(pd->stream, &read_data, &read_length);
        CHECK_SUCCESS_GOTO(ret, r == 0, unlock_and_fail);

        if (read_length <= 0) {
            pa_threaded_mainloop_wait(pd->mainloop);
            CHECK_DEAD_GOTO(pd, ret, unlock_and_fail);
        } else if (!read_data) {
            /* There's a hole in the stream, skip it. We could generate
                * silence, but that wouldn't work for compressed streams. */
            r = pa_stream_drop(pd->stream);
            CHECK_SUCCESS_GOTO(ret, r == 0, unlock_and_fail);
        }
    }

    if (av_new_packet(pkt, read_length) < 0) {
        ret = AVERROR(ENOMEM);
        goto unlock_and_fail;
    }

    dts = av_gettime();
    pa_operation_unref(pa_stream_update_timing_info(pd->stream, NULL, NULL));

    if (pa_stream_get_latency(pd->stream, &latency, &negative) >= 0) {
        enum AVCodecID codec_id =
            s->audio_codec_id == AV_CODEC_ID_NONE ? DEFAULT_CODEC_ID : s->audio_codec_id;
        int frame_size = ((av_get_bits_per_sample(codec_id) >> 3) * pd->channels);
        int frame_duration = read_length / frame_size;


        if (negative) {
            dts += latency;
        } else
            dts -= latency;
        if (pd->wallclock)
            pkt->pts = ff_timefilter_update(pd->timefilter, dts, pd->last_period);

        pd->last_period = frame_duration;
    } else {
        av_log(s, AV_LOG_WARNING, "pa_stream_get_latency() failed\n");
    }

    memcpy(pkt->data, read_data, read_length);
    pa_stream_drop(pd->stream);

    pa_threaded_mainloop_unlock(pd->mainloop);
    return 0;

unlock_and_fail:
    pa_threaded_mainloop_unlock(pd->mainloop);
    return ret;
}