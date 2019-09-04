#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int8_t ;
typedef  int int16_t ;
struct TYPE_8__ {size_t* permutated; } ;
struct TYPE_7__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* clear_block ) (int*) ;} ;
struct TYPE_9__ {int* dct_block; TYPE_3__ scantable; int /*<<< orphan*/  gb; TYPE_2__ vlc; TYPE_1__ bdsp; } ;
typedef  TYPE_4__ MimicContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 scalar_t__* vlcdec_lookup ; 

__attribute__((used)) static int vlc_decode_block(MimicContext *ctx, int num_coeffs, int qscale)
{
    int16_t *block = ctx->dct_block;
    unsigned int pos;

    ctx->bdsp.clear_block(block);

    block[0] = get_bits(&ctx->gb, 8) << 3;

    for (pos = 1; pos < num_coeffs; pos++) {
        uint32_t vlc, num_bits;
        int value;
        int coeff;

        vlc = get_vlc2(&ctx->gb, ctx->vlc.table, ctx->vlc.bits, 3);
        if (!vlc) /* end-of-block code */
            return 0;
        if (vlc == -1)
            return AVERROR_INVALIDDATA;

        /* pos_add and num_bits are coded in the vlc code */
        pos     += vlc & 15; // pos_add
        num_bits = vlc >> 4; // num_bits

        if (pos >= 64)
            return AVERROR_INVALIDDATA;

        value = get_bits(&ctx->gb, num_bits);

        /* FFmpeg's IDCT behaves somewhat different from the original code, so
         * a factor of 4 was added to the input */

        coeff = ((int8_t*)vlcdec_lookup[num_bits])[value];
        if (pos < 3)
            coeff *= 16;
        else /* TODO Use >> 10 instead of / 1001 */
            coeff = (coeff * qscale) / 1001;

        block[ctx->scantable.permutated[pos]] = coeff;
    }

    return 0;
}