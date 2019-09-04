#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_14__ {int frame_size; int channels; int /*<<< orphan*/  sample_fmt; TYPE_1__* priv_data; } ;
struct TYPE_13__ {int nb_samples; int /*<<< orphan*/ * extended_data; } ;
struct TYPE_12__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int decoder_buffer_size; scalar_t__ decoder_buffer; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  INT_PCM ;
typedef  TYPE_1__ FDKAACDecContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;
typedef  scalar_t__ AAC_DECODER_ERROR ;

/* Variables and functions */
 scalar_t__ AAC_DEC_NOT_ENOUGH_BITS ; 
 scalar_t__ AAC_DEC_OK ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ aacDecoder_DecodeFrame (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ aacDecoder_Fill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int av_get_bytes_per_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int get_stream_info (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int fdk_aac_decode_frame(AVCodecContext *avctx, void *data,
                                int *got_frame_ptr, AVPacket *avpkt)
{
    FDKAACDecContext *s = avctx->priv_data;
    AVFrame *frame = data;
    int ret;
    AAC_DECODER_ERROR err;
    UINT valid = avpkt->size;

    err = aacDecoder_Fill(s->handle, &avpkt->data, &avpkt->size, &valid);
    if (err != AAC_DEC_OK) {
        av_log(avctx, AV_LOG_ERROR, "aacDecoder_Fill() failed: %x\n", err);
        return AVERROR_INVALIDDATA;
    }

    err = aacDecoder_DecodeFrame(s->handle, (INT_PCM *) s->decoder_buffer, s->decoder_buffer_size / sizeof(INT_PCM), 0);
    if (err == AAC_DEC_NOT_ENOUGH_BITS) {
        ret = avpkt->size - valid;
        goto end;
    }
    if (err != AAC_DEC_OK) {
        av_log(avctx, AV_LOG_ERROR,
               "aacDecoder_DecodeFrame() failed: %x\n", err);
        ret = AVERROR_UNKNOWN;
        goto end;
    }

    if ((ret = get_stream_info(avctx)) < 0)
        goto end;
    frame->nb_samples = avctx->frame_size;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        goto end;

    memcpy(frame->extended_data[0], s->decoder_buffer,
           avctx->channels * avctx->frame_size *
           av_get_bytes_per_sample(avctx->sample_fmt));

    *got_frame_ptr = 1;
    ret = avpkt->size - valid;

end:
    return ret;
}