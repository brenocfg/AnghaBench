#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int avail_in; int* next_out; int avail_out; int /*<<< orphan*/  next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  int uint8_t ;
struct TYPE_17__ {TYPE_4__* previous_frame; TYPE_1__ zstream; } ;
typedef  TYPE_2__ ZeroCodecContext ;
struct TYPE_20__ {int height; int width; TYPE_2__* priv_data; } ;
struct TYPE_19__ {int** data; int key_frame; int* linesize; int /*<<< orphan*/  pict_type; } ;
struct TYPE_18__ {int flags; int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int AV_PKT_FLAG_KEY ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int av_frame_ref (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateReset (TYPE_1__*) ; 

__attribute__((used)) static int zerocodec_decode_frame(AVCodecContext *avctx, void *data,
                                  int *got_frame, AVPacket *avpkt)
{
    ZeroCodecContext *zc = avctx->priv_data;
    AVFrame *pic         = data;
    AVFrame *prev_pic    = zc->previous_frame;
    z_stream *zstream    = &zc->zstream;
    uint8_t *prev        = prev_pic->data[0];
    uint8_t *dst;
    int i, j, zret, ret;

    if (avpkt->flags & AV_PKT_FLAG_KEY) {
        pic->key_frame = 1;
        pic->pict_type = AV_PICTURE_TYPE_I;
    } else {
        if (!prev) {
            av_log(avctx, AV_LOG_ERROR, "Missing reference frame.\n");
            return AVERROR_INVALIDDATA;
        }

        prev += (avctx->height - 1) * prev_pic->linesize[0];

        pic->key_frame = 0;
        pic->pict_type = AV_PICTURE_TYPE_P;
    }

    zret = inflateReset(zstream);
    if (zret != Z_OK) {
        av_log(avctx, AV_LOG_ERROR, "Could not reset inflate: %d.\n", zret);
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_get_buffer(avctx, pic, AV_GET_BUFFER_FLAG_REF)) < 0)
        return ret;

    zstream->next_in  = avpkt->data;
    zstream->avail_in = avpkt->size;

    dst = pic->data[0] + (avctx->height - 1) * pic->linesize[0];

    /**
     * ZeroCodec has very simple interframe compression. If a value
     * is the same as the previous frame, set it to 0.
     */

    for (i = 0; i < avctx->height; i++) {
        zstream->next_out  = dst;
        zstream->avail_out = avctx->width << 1;

        zret = inflate(zstream, Z_SYNC_FLUSH);
        if (zret != Z_OK && zret != Z_STREAM_END) {
            av_log(avctx, AV_LOG_ERROR,
                   "Inflate failed with return code: %d.\n", zret);
            return AVERROR_INVALIDDATA;
        }

        if (!(avpkt->flags & AV_PKT_FLAG_KEY))
            for (j = 0; j < avctx->width << 1; j++)
                dst[j] += prev[j] & -!dst[j];

        prev -= prev_pic->linesize[0];
        dst  -= pic->linesize[0];
    }

    av_frame_unref(zc->previous_frame);
    if ((ret = av_frame_ref(zc->previous_frame, pic)) < 0)
        return ret;

    *got_frame = 1;

    return avpkt->size;
}