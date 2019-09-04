#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ codec_id; int channels; int /*<<< orphan*/ * priv_data; } ;
struct TYPE_9__ {int nb_samples; scalar_t__ extended_data; } ;
struct TYPE_8__ {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  DSDContext ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_DSD_LSBF ; 
 scalar_t__ AV_CODEC_ID_DSD_LSBF_PLANAR ; 
 scalar_t__ AV_CODEC_ID_DSD_MSBF_PLANAR ; 
 int /*<<< orphan*/  ff_dsd2pcm_translate (int /*<<< orphan*/ *,int,int,scalar_t__,int,float*,int) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame_ptr, AVPacket *avpkt)
{
    DSDContext * s = avctx->priv_data;
    AVFrame *frame = data;
    int ret, i;
    int lsbf = avctx->codec_id == AV_CODEC_ID_DSD_LSBF || avctx->codec_id == AV_CODEC_ID_DSD_LSBF_PLANAR;
    int src_next;
    int src_stride;

    frame->nb_samples = avpkt->size / avctx->channels;

    if (avctx->codec_id == AV_CODEC_ID_DSD_LSBF_PLANAR || avctx->codec_id == AV_CODEC_ID_DSD_MSBF_PLANAR) {
        src_next   = frame->nb_samples;
        src_stride = 1;
    } else {
        src_next   = 1;
        src_stride = avctx->channels;
    }

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    for (i = 0; i < avctx->channels; i++) {
        float * dst = ((float **)frame->extended_data)[i];
        ff_dsd2pcm_translate(&s[i], frame->nb_samples, lsbf,
            avpkt->data + i * src_next, src_stride,
            dst, 1);
    }

    *got_frame_ptr = 1;
    return frame->nb_samples * avctx->channels;
}