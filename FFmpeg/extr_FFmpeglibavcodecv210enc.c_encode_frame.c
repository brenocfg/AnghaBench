#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_15__ {int sample_factor_10; int sample_factor_8; int /*<<< orphan*/  (* pack_line_8 ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* pack_line_10 ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ V210EncContext ;
struct TYPE_19__ {int width; int height; TYPE_1__* priv_data; } ;
struct TYPE_18__ {scalar_t__ format; int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_17__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrameSideData ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_FRAME_DATA_A53_CC ; 
 int /*<<< orphan*/  AV_FRAME_DATA_AFD ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_YUV422P ; 
 scalar_t__ AV_PIX_FMT_YUV422P10 ; 
 int /*<<< orphan*/  AV_PKT_DATA_A53_CC ; 
 int /*<<< orphan*/  AV_PKT_DATA_AFD ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int CLIP (int /*<<< orphan*/ ) ; 
 int CLIP8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  WRITE_PIXELS (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WRITE_PIXELS8 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_3__* av_frame_get_side_data (TYPE_4__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ff_alloc_packet2 (TYPE_5__*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                        const AVFrame *pic, int *got_packet)
{
    V210EncContext *s = avctx->priv_data;
    int aligned_width = ((avctx->width + 47) / 48) * 48;
    int stride = aligned_width * 8 / 3;
    int line_padding = stride - ((avctx->width * 8 + 11) / 12) * 4;
    AVFrameSideData *side_data;
    int h, w, ret;
    uint8_t *dst;

    ret = ff_alloc_packet2(avctx, pkt, avctx->height * stride, avctx->height * stride);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error getting output packet.\n");
        return ret;
    }
    dst = pkt->data;

    if (pic->format == AV_PIX_FMT_YUV422P10) {
        const uint16_t *y = (const uint16_t *)pic->data[0];
        const uint16_t *u = (const uint16_t *)pic->data[1];
        const uint16_t *v = (const uint16_t *)pic->data[2];

        const int sample_size = 6 * s->sample_factor_10;
        const int sample_w    = avctx->width / sample_size;

        for (h = 0; h < avctx->height; h++) {
            uint32_t val;
            w = sample_w * sample_size;
            s->pack_line_10(y, u, v, dst, w);

            y += w;
            u += w >> 1;
            v += w >> 1;
            dst += sample_w * 16 * s->sample_factor_10;

            for (; w < avctx->width - 5; w += 6) {
                WRITE_PIXELS(u, y, v);
                WRITE_PIXELS(y, u, y);
                WRITE_PIXELS(v, y, u);
                WRITE_PIXELS(y, v, y);
            }
            if (w < avctx->width - 1) {
                WRITE_PIXELS(u, y, v);

                val = CLIP(*y++);
                if (w == avctx->width - 2) {
                    AV_WL32(dst, val);
                    dst += 4;
                }
            }
            if (w < avctx->width - 3) {
                val |= (CLIP(*u++) << 10) | (CLIP(*y++) << 20);
                AV_WL32(dst, val);
                dst += 4;

                val = CLIP(*v++) | (CLIP(*y++) << 10);
                AV_WL32(dst, val);
                dst += 4;
            }

            memset(dst, 0, line_padding);
            dst += line_padding;
            y += pic->linesize[0] / 2 - avctx->width;
            u += pic->linesize[1] / 2 - avctx->width / 2;
            v += pic->linesize[2] / 2 - avctx->width / 2;
        }
    } else if(pic->format == AV_PIX_FMT_YUV422P) {
        const uint8_t *y = pic->data[0];
        const uint8_t *u = pic->data[1];
        const uint8_t *v = pic->data[2];

        const int sample_size = 12 * s->sample_factor_8;
        const int sample_w    = avctx->width / sample_size;

        for (h = 0; h < avctx->height; h++) {
            uint32_t val;
            w = sample_w * sample_size;
            s->pack_line_8(y, u, v, dst, w);

            y += w;
            u += w >> 1;
            v += w >> 1;
            dst += sample_w * 32 * s->sample_factor_8;

            for (; w < avctx->width - 5; w += 6) {
                WRITE_PIXELS8(u, y, v);
                WRITE_PIXELS8(y, u, y);
                WRITE_PIXELS8(v, y, u);
                WRITE_PIXELS8(y, v, y);
            }
            if (w < avctx->width - 1) {
                WRITE_PIXELS8(u, y, v);

                val = CLIP8(*y++) << 2;
                if (w == avctx->width - 2) {
                    AV_WL32(dst, val);
                    dst += 4;
                }
            }
            if (w < avctx->width - 3) {
                val |= (CLIP8(*u++) << 12) | (CLIP8(*y++) << 22);
                AV_WL32(dst, val);
                dst += 4;

                val = (CLIP8(*v++) << 2) | (CLIP8(*y++) << 12);
                AV_WL32(dst, val);
                dst += 4;
            }
            memset(dst, 0, line_padding);
            dst += line_padding;

            y += pic->linesize[0] - avctx->width;
            u += pic->linesize[1] - avctx->width / 2;
            v += pic->linesize[2] - avctx->width / 2;
        }
    }

    side_data = av_frame_get_side_data(pic, AV_FRAME_DATA_A53_CC);
    if (side_data && side_data->size) {
        uint8_t *buf = av_packet_new_side_data(pkt, AV_PKT_DATA_A53_CC, side_data->size);
        if (!buf)
            return AVERROR(ENOMEM);
        memcpy(buf, side_data->data, side_data->size);
    }

    side_data = av_frame_get_side_data(pic, AV_FRAME_DATA_AFD);
    if (side_data && side_data->size) {
        uint8_t *buf = av_packet_new_side_data(pkt, AV_PKT_DATA_AFD, side_data->size);
        if (!buf)
            return AVERROR(ENOMEM);
        memcpy(buf, side_data->data, side_data->size);
    }

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}