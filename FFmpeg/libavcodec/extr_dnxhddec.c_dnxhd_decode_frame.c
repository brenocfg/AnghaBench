#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_21__ {void* f; } ;
typedef  TYPE_3__ ThreadFrame ;
struct TYPE_25__ {int thread_count; scalar_t__ width; scalar_t__ height; scalar_t__ pix_fmt; int /*<<< orphan*/  (* execute2 ) (TYPE_7__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;TYPE_4__* priv_data; } ;
struct TYPE_24__ {int key_frame; scalar_t__ interlaced_frame; int /*<<< orphan*/  pict_type; } ;
struct TYPE_23__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_22__ {scalar_t__ width; scalar_t__ height; scalar_t__ pix_fmt; int buf_size; int data_offset; int bit_depth; int /*<<< orphan*/  avctx; TYPE_2__* rows; scalar_t__ act; TYPE_1__* cid_table; int /*<<< orphan*/  mb_height; int /*<<< orphan*/  const* buf; } ;
struct TYPE_20__ {int format; scalar_t__ errors; } ;
struct TYPE_19__ {scalar_t__ coding_unit_size; } ;
typedef  TYPE_4__ DNXHDContext ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PIX_FMT_GBRP10 ; 
 scalar_t__ AV_PIX_FMT_GBRP12 ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 scalar_t__ AV_PIX_FMT_YUV444P10 ; 
 scalar_t__ AV_PIX_FMT_YUV444P12 ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 int dnxhd_decode_header (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  dnxhd_decode_row ; 
 int /*<<< orphan*/  ff_dlog (TYPE_7__*,char*,int) ; 
 int ff_set_dimensions (TYPE_7__*,scalar_t__,scalar_t__) ; 
 int ff_thread_get_buffer (TYPE_7__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dnxhd_decode_frame(AVCodecContext *avctx, void *data,
                              int *got_frame, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    DNXHDContext *ctx = avctx->priv_data;
    ThreadFrame frame = { .f = data };
    AVFrame *picture = data;
    int first_field = 1;
    int ret, i;

    ff_dlog(avctx, "frame size %d\n", buf_size);

    for (i = 0; i < avctx->thread_count; i++)
        ctx->rows[i].format = -1;

decode_coding_unit:
    if ((ret = dnxhd_decode_header(ctx, picture, buf, buf_size, first_field)) < 0)
        return ret;

    if ((avctx->width || avctx->height) &&
        (ctx->width != avctx->width || ctx->height != avctx->height)) {
        av_log(avctx, AV_LOG_WARNING, "frame size changed: %dx%d -> %ux%u\n",
               avctx->width, avctx->height, ctx->width, ctx->height);
        first_field = 1;
    }
    if (avctx->pix_fmt != AV_PIX_FMT_NONE && avctx->pix_fmt != ctx->pix_fmt) {
        av_log(avctx, AV_LOG_WARNING, "pix_fmt changed: %s -> %s\n",
               av_get_pix_fmt_name(avctx->pix_fmt), av_get_pix_fmt_name(ctx->pix_fmt));
        first_field = 1;
    }

    avctx->pix_fmt = ctx->pix_fmt;
    ret = ff_set_dimensions(avctx, ctx->width, ctx->height);
    if (ret < 0)
        return ret;

    if (first_field) {
        if ((ret = ff_thread_get_buffer(avctx, &frame, 0)) < 0)
            return ret;
        picture->pict_type = AV_PICTURE_TYPE_I;
        picture->key_frame = 1;
    }

    ctx->buf_size = buf_size - ctx->data_offset;
    ctx->buf = buf + ctx->data_offset;
    avctx->execute2(avctx, dnxhd_decode_row, picture, NULL, ctx->mb_height);

    if (first_field && picture->interlaced_frame) {
        buf      += ctx->cid_table->coding_unit_size;
        buf_size -= ctx->cid_table->coding_unit_size;
        first_field = 0;
        goto decode_coding_unit;
    }

    ret = 0;
    for (i = 0; i < avctx->thread_count; i++) {
        ret += ctx->rows[i].errors;
        ctx->rows[i].errors = 0;
    }

    if (ctx->act) {
        static int act_warned;
        int format = ctx->rows[0].format;
        for (i = 1; i < avctx->thread_count; i++) {
            if (ctx->rows[i].format != format &&
                ctx->rows[i].format != -1 /* not run */) {
                format = 2;
                break;
            }
        }
        switch (format) {
        case -1:
        case 2:
            if (!act_warned) {
                act_warned = 1;
                av_log(ctx->avctx, AV_LOG_ERROR,
                       "Unsupported: variable ACT flag.\n");
            }
            break;
        case 0:
            ctx->pix_fmt = ctx->bit_depth==10
                         ? AV_PIX_FMT_GBRP10 : AV_PIX_FMT_GBRP12;
            break;
        case 1:
            ctx->pix_fmt = ctx->bit_depth==10
                         ? AV_PIX_FMT_YUV444P10 : AV_PIX_FMT_YUV444P12;
            break;
        }
    }
    avctx->pix_fmt = ctx->pix_fmt;
    if (ret) {
        av_log(ctx->avctx, AV_LOG_ERROR, "%d lines with errors\n", ret);
        return AVERROR_INVALIDDATA;
    }

    *got_frame = 1;
    return avpkt->size;
}