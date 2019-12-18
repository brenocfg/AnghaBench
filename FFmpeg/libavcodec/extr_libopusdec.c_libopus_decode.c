#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float d; scalar_t__ i; } ;
struct libopus_context {TYPE_1__ gain; int /*<<< orphan*/  dec; } ;
typedef  int /*<<< orphan*/  opus_int16 ;
typedef  int int64_t ;
typedef  int int16_t ;
struct TYPE_13__ {scalar_t__ sample_fmt; int channels; struct libopus_context* priv_data; } ;
struct TYPE_12__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_SAMPLE_FMT_FLT ; 
 scalar_t__ AV_SAMPLE_FMT_S16 ; 
 int MAX_FRAME_SIZE ; 
 int av_clip_int16 (int) ; 
 float av_clipf (float,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_opus_error_to_averror (int) ; 
 int opus_multistream_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int opus_multistream_decode_float (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_strerror (int) ; 

__attribute__((used)) static int libopus_decode(AVCodecContext *avc, void *data,
                          int *got_frame_ptr, AVPacket *pkt)
{
    struct libopus_context *opus = avc->priv_data;
    AVFrame *frame               = data;
    int ret, nb_samples;

    frame->nb_samples = MAX_FRAME_SIZE;
    if ((ret = ff_get_buffer(avc, frame, 0)) < 0)
        return ret;

    if (avc->sample_fmt == AV_SAMPLE_FMT_S16)
        nb_samples = opus_multistream_decode(opus->dec, pkt->data, pkt->size,
                                             (opus_int16 *)frame->data[0],
                                             frame->nb_samples, 0);
    else
        nb_samples = opus_multistream_decode_float(opus->dec, pkt->data, pkt->size,
                                                   (float *)frame->data[0],
                                                   frame->nb_samples, 0);

    if (nb_samples < 0) {
        av_log(avc, AV_LOG_ERROR, "Decoding error: %s\n",
               opus_strerror(nb_samples));
        return ff_opus_error_to_averror(nb_samples);
    }

#ifndef OPUS_SET_GAIN
    {
        int i = avc->channels * nb_samples;
        if (avc->sample_fmt == AV_SAMPLE_FMT_FLT) {
            float *pcm = (float *)frame->data[0];
            for (; i > 0; i--, pcm++)
                *pcm = av_clipf(*pcm * opus->gain.d, -1, 1);
        } else {
            int16_t *pcm = (int16_t *)frame->data[0];
            for (; i > 0; i--, pcm++)
                *pcm = av_clip_int16(((int64_t)opus->gain.i * *pcm) >> 16);
        }
    }
#endif

    frame->nb_samples = nb_samples;
    *got_frame_ptr    = 1;

    return pkt->size;
}