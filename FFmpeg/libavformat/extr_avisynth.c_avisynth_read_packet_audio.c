#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* int64_t ;
struct TYPE_20__ {scalar_t__ num_audio_samples; int fps_denominator; scalar_t__ num_frames; int nchannels; int /*<<< orphan*/  audio_samples_per_second; int /*<<< orphan*/  fps_numerator; } ;
struct TYPE_19__ {char* (* avs_clip_get_error ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* avs_get_audio ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int) ;} ;
struct TYPE_18__ {TYPE_1__* priv_data; } ;
struct TYPE_17__ {int size; int duration; int /*<<< orphan*/ * data; int /*<<< orphan*/  stream_index; void* dts; void* pts; } ;
struct TYPE_16__ {int den; int /*<<< orphan*/  num; } ;
struct TYPE_15__ {scalar_t__ curr_sample; scalar_t__ curr_frame; int error; int /*<<< orphan*/  clip; int /*<<< orphan*/  curr_stream; TYPE_6__* vi; } ;
typedef  TYPE_1__ AviSynthContext ;
typedef  TYPE_2__ AVRational ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ av_new_packet (TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int av_rescale_q (int,TYPE_2__,TYPE_2__) ; 
 int avs_bytes_per_channel_sample (TYPE_6__*) ; 
 scalar_t__ avs_has_video (TYPE_6__*) ; 
 TYPE_5__ avs_library ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int) ; 
 char* stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avisynth_read_packet_audio(AVFormatContext *s, AVPacket *pkt,
                                      int discard)
{
    AviSynthContext *avs = s->priv_data;
    AVRational fps, samplerate;
    int samples;
    int64_t n;
    const char *error;

    if (avs->curr_sample >= avs->vi->num_audio_samples)
        return AVERROR_EOF;

    fps.num        = avs->vi->fps_numerator;
    fps.den        = avs->vi->fps_denominator;
    samplerate.num = avs->vi->audio_samples_per_second;
    samplerate.den = 1;

    if (avs_has_video(avs->vi)) {
        if (avs->curr_frame < avs->vi->num_frames)
            samples = av_rescale_q(avs->curr_frame, samplerate, fps) -
                      avs->curr_sample;
        else
            samples = av_rescale_q(1, samplerate, fps);
    } else {
        samples = 1000;
    }

    /* After seeking, audio may catch up with video. */
    if (samples <= 0) {
        pkt->size = 0;
        pkt->data = NULL;
        return 0;
    }

    if (avs->curr_sample + samples > avs->vi->num_audio_samples)
        samples = avs->vi->num_audio_samples - avs->curr_sample;

    /* This must happen even if the stream is discarded to prevent desync. */
    n                 = avs->curr_sample;
    avs->curr_sample += samples;
    if (discard)
        return 0;

    pkt->size = avs_bytes_per_channel_sample(avs->vi) *
                samples * avs->vi->nchannels;
    if (!pkt->size)
        return AVERROR_UNKNOWN;

    if (av_new_packet(pkt, pkt->size) < 0)
        return AVERROR(ENOMEM);

    pkt->pts      = n;
    pkt->dts      = n;
    pkt->duration = samples;
    pkt->stream_index = avs->curr_stream;

    avs_library.avs_get_audio(avs->clip, pkt->data, n, samples);
    error = avs_library.avs_clip_get_error(avs->clip);
    if (error) {
        av_log(s, AV_LOG_ERROR, "%s\n", error);
        avs->error = 1;
        av_packet_unref(pkt);
        return AVERROR_UNKNOWN;
    }
    return 0;
}