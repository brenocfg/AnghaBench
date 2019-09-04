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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {TYPE_1__* avctx; } ;
typedef  TYPE_2__ VBLEContext ;
struct TYPE_17__ {void* f; } ;
typedef  TYPE_3__ ThreadFrame ;
struct TYPE_20__ {int width; int height; TYPE_2__* priv_data; } ;
struct TYPE_19__ {int key_frame; int /*<<< orphan*/  pict_type; } ;
struct TYPE_18__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {int flags; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int AV_RL32 (int /*<<< orphan*/  const*) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_thread_get_buffer (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  vble_restore_plane (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *,int,int,int,int) ; 
 scalar_t__ vble_unpack (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vble_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                             AVPacket *avpkt)
{
    VBLEContext *ctx = avctx->priv_data;
    AVFrame *pic     = data;
    GetBitContext gb;
    const uint8_t *src = avpkt->data;
    int version;
    int offset = 0;
    int width_uv = avctx->width / 2, height_uv = avctx->height / 2;
    int ret;
    ThreadFrame frame = { .f = data };

    if (avpkt->size < 4 || avpkt->size - 4 > INT_MAX/8) {
        av_log(avctx, AV_LOG_ERROR, "Invalid packet size\n");
        return AVERROR_INVALIDDATA;
    }

    /* Allocate buffer */
    if ((ret = ff_thread_get_buffer(avctx, &frame, 0)) < 0)
        return ret;

    /* Set flags */
    pic->key_frame = 1;
    pic->pict_type = AV_PICTURE_TYPE_I;

    /* Version should always be 1 */
    version = AV_RL32(src);

    if (version != 1)
        av_log(avctx, AV_LOG_WARNING, "Unsupported VBLE Version: %d\n", version);

    init_get_bits(&gb, src + 4, (avpkt->size - 4) * 8);

    /* Unpack */
    if (vble_unpack(ctx, &gb) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Invalid Code\n");
        return AVERROR_INVALIDDATA;
    }

    /* Restore planes. Should be almost identical to Huffyuv's. */
    vble_restore_plane(ctx, pic, &gb, 0, offset, avctx->width, avctx->height);

    /* Chroma */
    if (!(ctx->avctx->flags & AV_CODEC_FLAG_GRAY)) {
        offset += avctx->width * avctx->height;
        vble_restore_plane(ctx, pic, &gb, 1, offset, width_uv, height_uv);

        offset += width_uv * height_uv;
        vble_restore_plane(ctx, pic, &gb, 2, offset, width_uv, height_uv);
    }

    *got_frame       = 1;

    return avpkt->size;
}