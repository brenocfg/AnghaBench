#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_6__ {int pitch; int width; int* small_codebook; int* codebook; int /*<<< orphan*/  gb; int /*<<< orphan*/  frm0; int /*<<< orphan*/  frm1; int /*<<< orphan*/  frm2; } ;
typedef  TYPE_1__ SANMVideoContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 size_t bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_block (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  fill_block (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  good_mvec (TYPE_1__*,int,int,int,int,int) ; 
 int** motion_vectors ; 
 int /*<<< orphan*/  opcode_0xf7 (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  opcode_0xf8 (TYPE_1__*,int,int,int,int) ; 

__attribute__((used)) static int codec2subblock(SANMVideoContext *ctx, int cx, int cy, int blk_size)
{
    int16_t mx, my, index;
    int opcode;

    if (bytestream2_get_bytes_left(&ctx->gb) < 1)
        return AVERROR_INVALIDDATA;

    opcode = bytestream2_get_byteu(&ctx->gb);

    switch (opcode) {
    default:
        mx = motion_vectors[opcode][0];
        my = motion_vectors[opcode][1];

        if (good_mvec(ctx, cx, cy, mx, my, blk_size)) {
            copy_block(ctx->frm0 + cx      + ctx->pitch *  cy,
                       ctx->frm2 + cx + mx + ctx->pitch * (cy + my),
                       blk_size, ctx->pitch);
        }
        break;
    case 0xF5:
        if (bytestream2_get_bytes_left(&ctx->gb) < 2)
            return AVERROR_INVALIDDATA;
        index = bytestream2_get_le16u(&ctx->gb);

        mx = index % ctx->width;
        my = index / ctx->width;

        if (good_mvec(ctx, cx, cy, mx, my, blk_size)) {
            copy_block(ctx->frm0 + cx      + ctx->pitch *  cy,
                       ctx->frm2 + cx + mx + ctx->pitch * (cy + my),
                       blk_size, ctx->pitch);
        }
        break;
    case 0xF6:
        copy_block(ctx->frm0 + cx + ctx->pitch * cy,
                   ctx->frm1 + cx + ctx->pitch * cy,
                   blk_size, ctx->pitch);
        break;
    case 0xF7:
        opcode_0xf7(ctx, cx, cy, blk_size, ctx->pitch);
        break;

    case 0xF8:
        opcode_0xf8(ctx, cx, cy, blk_size, ctx->pitch);
        break;
    case 0xF9:
    case 0xFA:
    case 0xFB:
    case 0xFC:
        fill_block(ctx->frm0 + cx + cy * ctx->pitch,
                   ctx->small_codebook[opcode - 0xf9], blk_size, ctx->pitch);
        break;
    case 0xFD:
        if (bytestream2_get_bytes_left(&ctx->gb) < 1)
            return AVERROR_INVALIDDATA;
        fill_block(ctx->frm0 + cx + cy * ctx->pitch,
                   ctx->codebook[bytestream2_get_byteu(&ctx->gb)], blk_size, ctx->pitch);
        break;
    case 0xFE:
        if (bytestream2_get_bytes_left(&ctx->gb) < 2)
            return AVERROR_INVALIDDATA;
        fill_block(ctx->frm0 + cx + cy * ctx->pitch,
                   bytestream2_get_le16u(&ctx->gb), blk_size, ctx->pitch);
        break;
    case 0xFF:
        if (blk_size == 2) {
            opcode_0xf8(ctx, cx, cy, blk_size, ctx->pitch);
        } else {
            blk_size >>= 1;
            if (codec2subblock(ctx, cx, cy, blk_size))
                return AVERROR_INVALIDDATA;
            if (codec2subblock(ctx, cx + blk_size, cy, blk_size))
                return AVERROR_INVALIDDATA;
            if (codec2subblock(ctx, cx, cy + blk_size, blk_size))
                return AVERROR_INVALIDDATA;
            if (codec2subblock(ctx, cx + blk_size, cy + blk_size, blk_size))
                return AVERROR_INVALIDDATA;
        }
        break;
    }
    return 0;
}