#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {scalar_t__ pix_fmt; } ;
struct TYPE_9__ {TYPE_1__* f; } ;
struct TYPE_10__ {int hdr_state; int last_w; int cur_w; int last_h; int cur_h; int last_x_offset; int x_offset; int last_y_offset; int y_offset; int last_dispose_op; int dispose_op; int width; int height; int blend_op; int /*<<< orphan*/  has_trns; TYPE_2__ previous_picture; int /*<<< orphan*/  gb; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ PNGDecContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int APNG_BLEND_OP_OVER ; 
 int APNG_BLEND_OP_SOURCE ; 
 int APNG_DISPOSE_OP_BACKGROUND ; 
 int APNG_DISPOSE_OP_PREVIOUS ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_GRAY16BE ; 
 scalar_t__ AV_PIX_FMT_GRAY8 ; 
 scalar_t__ AV_PIX_FMT_MONOBLACK ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 scalar_t__ AV_PIX_FMT_RGB48BE ; 
 int PNG_IHDR ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int bytestream2_get_be32 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_fctl_chunk(AVCodecContext *avctx, PNGDecContext *s,
                             uint32_t length)
{
    uint32_t sequence_number;
    int cur_w, cur_h, x_offset, y_offset, dispose_op, blend_op;

    if (length != 26)
        return AVERROR_INVALIDDATA;

    if (!(s->hdr_state & PNG_IHDR)) {
        av_log(avctx, AV_LOG_ERROR, "fctl before IHDR\n");
        return AVERROR_INVALIDDATA;
    }

    s->last_w = s->cur_w;
    s->last_h = s->cur_h;
    s->last_x_offset = s->x_offset;
    s->last_y_offset = s->y_offset;
    s->last_dispose_op = s->dispose_op;

    sequence_number = bytestream2_get_be32(&s->gb);
    cur_w           = bytestream2_get_be32(&s->gb);
    cur_h           = bytestream2_get_be32(&s->gb);
    x_offset        = bytestream2_get_be32(&s->gb);
    y_offset        = bytestream2_get_be32(&s->gb);
    bytestream2_skip(&s->gb, 4); /* delay_num (2), delay_den (2) */
    dispose_op      = bytestream2_get_byte(&s->gb);
    blend_op        = bytestream2_get_byte(&s->gb);
    bytestream2_skip(&s->gb, 4); /* crc */

    if (sequence_number == 0 &&
        (cur_w != s->width ||
         cur_h != s->height ||
         x_offset != 0 ||
         y_offset != 0) ||
        cur_w <= 0 || cur_h <= 0 ||
        x_offset < 0 || y_offset < 0 ||
        cur_w > s->width - x_offset|| cur_h > s->height - y_offset)
            return AVERROR_INVALIDDATA;

    if (blend_op != APNG_BLEND_OP_OVER && blend_op != APNG_BLEND_OP_SOURCE) {
        av_log(avctx, AV_LOG_ERROR, "Invalid blend_op %d\n", blend_op);
        return AVERROR_INVALIDDATA;
    }

    if ((sequence_number == 0 || !s->previous_picture.f->data[0]) &&
        dispose_op == APNG_DISPOSE_OP_PREVIOUS) {
        // No previous frame to revert to for the first frame
        // Spec says to just treat it as a APNG_DISPOSE_OP_BACKGROUND
        dispose_op = APNG_DISPOSE_OP_BACKGROUND;
    }

    if (blend_op == APNG_BLEND_OP_OVER && !s->has_trns && (
            avctx->pix_fmt == AV_PIX_FMT_RGB24 ||
            avctx->pix_fmt == AV_PIX_FMT_RGB48BE ||
            avctx->pix_fmt == AV_PIX_FMT_PAL8 ||
            avctx->pix_fmt == AV_PIX_FMT_GRAY8 ||
            avctx->pix_fmt == AV_PIX_FMT_GRAY16BE ||
            avctx->pix_fmt == AV_PIX_FMT_MONOBLACK
        )) {
        // APNG_BLEND_OP_OVER is the same as APNG_BLEND_OP_SOURCE when there is no alpha channel
        blend_op = APNG_BLEND_OP_SOURCE;
    }

    s->cur_w      = cur_w;
    s->cur_h      = cur_h;
    s->x_offset   = x_offset;
    s->y_offset   = y_offset;
    s->dispose_op = dispose_op;
    s->blend_op   = blend_op;

    return 0;
}