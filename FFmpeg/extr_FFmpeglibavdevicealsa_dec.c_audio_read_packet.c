#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ snd_pcm_sframes_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {TYPE_1__* priv_data; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  pts; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int period_size; int frame_size; int last_period; int /*<<< orphan*/  timefilter; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ AlsaData ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  av_gettime () ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ av_new_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 scalar_t__ av_rescale (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_alsa_xrun_recover (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ff_timefilter_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_timefilter_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_delay (int /*<<< orphan*/ ,scalar_t__*) ; 
 int snd_pcm_readi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 

__attribute__((used)) static int audio_read_packet(AVFormatContext *s1, AVPacket *pkt)
{
    AlsaData *s  = s1->priv_data;
    int res;
    int64_t dts;
    snd_pcm_sframes_t delay = 0;

    if (av_new_packet(pkt, s->period_size * s->frame_size) < 0) {
        return AVERROR(EIO);
    }

    while ((res = snd_pcm_readi(s->h, pkt->data, s->period_size)) < 0) {
        if (res == -EAGAIN) {
            av_packet_unref(pkt);

            return AVERROR(EAGAIN);
        }
        if (ff_alsa_xrun_recover(s1, res) < 0) {
            av_log(s1, AV_LOG_ERROR, "ALSA read error: %s\n",
                   snd_strerror(res));
            av_packet_unref(pkt);

            return AVERROR(EIO);
        }
        ff_timefilter_reset(s->timefilter);
    }

    dts = av_gettime();
    snd_pcm_delay(s->h, &delay);
    dts -= av_rescale(delay + res, 1000000, s->sample_rate);
    pkt->pts = ff_timefilter_update(s->timefilter, dts, s->last_period);
    s->last_period = res;

    pkt->size = res * s->frame_size;

    return 0;
}