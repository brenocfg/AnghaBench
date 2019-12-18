#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_8__ {int /*<<< orphan*/  dcb; int /*<<< orphan*/ * dc_vlc; scalar_t__ interlaced; TYPE_1__ cbp_vlc; TYPE_2__* slice; } ;
struct TYPE_7__ {int** block; int /*<<< orphan*/  gb; } ;
typedef  TYPE_2__ HQXSlice ;
typedef  TYPE_3__ HQXContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int decode_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ,int*,int*) ; 
 size_t get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hqx_quant_chroma ; 
 int /*<<< orphan*/  hqx_quant_luma ; 
 int** hqx_quants ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_blocks (TYPE_3__*,int,int,int,int,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hqx_decode_422a(HQXContext *ctx, int slice_no, int x, int y)
{
    HQXSlice *slice = &ctx->slice[slice_no];
    GetBitContext *gb = &slice->gb;
    const int *quants;
    int flag = 0;
    int last_dc;
    int i, ret;
    int cbp;

    cbp = get_vlc2(gb, ctx->cbp_vlc.table, ctx->cbp_vlc.bits, 1);

    for (i = 0; i < 12; i++)
        memset(slice->block[i], 0, sizeof(**slice->block) * 64);
    for (i = 0; i < 12; i++)
        slice->block[i][0] = -0x800;
    if (cbp) {
        if (ctx->interlaced)
            flag = get_bits1(gb);

        quants = hqx_quants[get_bits(gb, 4)];

        cbp |= cbp << 4; // alpha CBP
        if (cbp & 0x3)   // chroma CBP - top
            cbp |= 0x500;
        if (cbp & 0xC)   // chroma CBP - bottom
            cbp |= 0xA00;
        for (i = 0; i < 12; i++) {
            if (i == 0 || i == 4 || i == 8 || i == 10)
                last_dc = 0;
            if (cbp & (1 << i)) {
                int vlc_index = ctx->dcb - 9;
                ret = decode_block(gb, &ctx->dc_vlc[vlc_index], quants,
                                   ctx->dcb, slice->block[i], &last_dc);
                if (ret < 0)
                    return ret;
            }
        }
    }

    put_blocks(ctx, 3, x,      y, flag, slice->block[ 0], slice->block[ 2], hqx_quant_luma);
    put_blocks(ctx, 3, x + 8,  y, flag, slice->block[ 1], slice->block[ 3], hqx_quant_luma);
    put_blocks(ctx, 0, x,      y, flag, slice->block[ 4], slice->block[ 6], hqx_quant_luma);
    put_blocks(ctx, 0, x + 8,  y, flag, slice->block[ 5], slice->block[ 7], hqx_quant_luma);
    put_blocks(ctx, 2, x >> 1, y, flag, slice->block[ 8], slice->block[ 9], hqx_quant_chroma);
    put_blocks(ctx, 1, x >> 1, y, flag, slice->block[10], slice->block[11], hqx_quant_chroma);

    return 0;
}