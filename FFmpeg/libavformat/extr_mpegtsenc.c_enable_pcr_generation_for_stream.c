#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_15__ {scalar_t__ codec_type; scalar_t__ sample_rate; } ;
struct TYPE_14__ {TYPE_3__* priv_data; } ;
struct TYPE_10__ {int den; scalar_t__ num; } ;
struct TYPE_13__ {TYPE_1__ avg_frame_rate; TYPE_9__* codecpar; TYPE_2__* priv_data; } ;
struct TYPE_12__ {int mux_rate; int pcr_period_ms; scalar_t__ first_pcr; } ;
struct TYPE_11__ {int pcr_period; scalar_t__ last_pcr; } ;
typedef  TYPE_2__ MpegTSWriteStream ;
typedef  TYPE_3__ MpegTSWrite ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_ROUND_UP ; 
 int PCR_RETRANS_TIME ; 
 int PCR_TIME_BASE ; 
 int av_get_audio_frame_duration2 (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int av_rescale (int,int,int) ; 
 int av_rescale_rnd (int,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_pcr_generation_for_stream(AVFormatContext *s, AVStream *pcr_st)
{
    MpegTSWrite *ts = s->priv_data;
    MpegTSWriteStream *ts_st = pcr_st->priv_data;

    if (ts->mux_rate > 1 || ts->pcr_period_ms >= 0) {
        int pcr_period_ms = ts->pcr_period_ms == -1 ? PCR_RETRANS_TIME : ts->pcr_period_ms;
        ts_st->pcr_period = av_rescale(pcr_period_ms, PCR_TIME_BASE, 1000);
    } else {
        /* By default, for VBR we select the highest multiple of frame duration which is less than 100 ms. */
        int64_t frame_period = 0;
        if (pcr_st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            int frame_size = av_get_audio_frame_duration2(pcr_st->codecpar, 0);
            if (!frame_size) {
               av_log(s, AV_LOG_WARNING, "frame size not set\n");
               frame_size = 512;
            }
            frame_period = av_rescale_rnd(frame_size, PCR_TIME_BASE, pcr_st->codecpar->sample_rate, AV_ROUND_UP);
        } else if (pcr_st->avg_frame_rate.num) {
            frame_period = av_rescale_rnd(pcr_st->avg_frame_rate.den, PCR_TIME_BASE, pcr_st->avg_frame_rate.num, AV_ROUND_UP);
        }
        if (frame_period > 0 && frame_period <= PCR_TIME_BASE / 10)
            ts_st->pcr_period = frame_period * (PCR_TIME_BASE / 10 / frame_period);
        else
            ts_st->pcr_period = 1;
    }

    // output a PCR as soon as possible
    ts_st->last_pcr   = ts->first_pcr - ts_st->pcr_period;
}