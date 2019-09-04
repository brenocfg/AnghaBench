#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int ptrdiff_t ;
struct TYPE_5__ {int pitch; int height; int prev_seq; int rotate_code; int /*<<< orphan*/  avctx; scalar_t__ frm1; scalar_t__ frm0; scalar_t__ frm2; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ SANMVideoContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bytestream2_get_bufferu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_block (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  rle_decode (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int old_codec47(SANMVideoContext *ctx, int top,
                       int left, int width, int height)
{
    uint32_t decoded_size;
    int i, j;
    ptrdiff_t stride = ctx->pitch;
    uint8_t *dst   = (uint8_t *)ctx->frm0 + left + top * stride;
    uint8_t *prev1 = (uint8_t *)ctx->frm1;
    uint8_t *prev2 = (uint8_t *)ctx->frm2;
    int tbl_pos = bytestream2_tell(&ctx->gb);
    int seq     = bytestream2_get_le16(&ctx->gb);
    int compr   = bytestream2_get_byte(&ctx->gb);
    int new_rot = bytestream2_get_byte(&ctx->gb);
    int skip    = bytestream2_get_byte(&ctx->gb);

    bytestream2_skip(&ctx->gb, 9);
    decoded_size = bytestream2_get_le32(&ctx->gb);
    bytestream2_skip(&ctx->gb, 8);

    if (decoded_size > ctx->height * stride - left - top * stride) {
        decoded_size = ctx->height * stride - left - top * stride;
        av_log(ctx->avctx, AV_LOG_WARNING, "Decoded size is too large.\n");
    }

    if (skip & 1)
        bytestream2_skip(&ctx->gb, 0x8080);
    if (!seq) {
        ctx->prev_seq = -1;
        memset(prev1, 0, ctx->height * stride);
        memset(prev2, 0, ctx->height * stride);
    }

    switch (compr) {
    case 0:
        if (bytestream2_get_bytes_left(&ctx->gb) < width * height)
            return AVERROR_INVALIDDATA;
        for (j = 0; j < height; j++) {
            bytestream2_get_bufferu(&ctx->gb, dst, width);
            dst += stride;
        }
        break;
    case 1:
        if (bytestream2_get_bytes_left(&ctx->gb) < ((width + 1) >> 1) * ((height + 1) >> 1))
            return AVERROR_INVALIDDATA;
        for (j = 0; j < height; j += 2) {
            for (i = 0; i < width; i += 2) {
                dst[i] =
                dst[i + 1] =
                dst[stride + i] =
                dst[stride + i + 1] = bytestream2_get_byteu(&ctx->gb);
            }
            dst += stride * 2;
        }
        break;
    case 2:
        if (seq == ctx->prev_seq + 1) {
            for (j = 0; j < height; j += 8) {
                for (i = 0; i < width; i += 8)
                    if (process_block(ctx, dst + i, prev1 + i, prev2 + i, stride,
                                      tbl_pos + 8, 8))
                        return AVERROR_INVALIDDATA;
                dst   += stride * 8;
                prev1 += stride * 8;
                prev2 += stride * 8;
            }
        }
        break;
    case 3:
        memcpy(ctx->frm0, ctx->frm2, ctx->pitch * ctx->height);
        break;
    case 4:
        memcpy(ctx->frm0, ctx->frm1, ctx->pitch * ctx->height);
        break;
    case 5:
        if (rle_decode(ctx, dst, decoded_size))
            return AVERROR_INVALIDDATA;
        break;
    default:
        avpriv_report_missing_feature(ctx->avctx,
                                      "Subcodec 47 compression %d", compr);
        return AVERROR_PATCHWELCOME;
    }
    if (seq == ctx->prev_seq + 1)
        ctx->rotate_code = new_rot;
    else
        ctx->rotate_code = 0;
    ctx->prev_seq = seq;

    return 0;
}