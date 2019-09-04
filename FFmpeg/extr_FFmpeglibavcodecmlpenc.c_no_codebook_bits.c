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
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_8__ {int offset; int lsb_bits; int bitcount; int min; int max; } ;
struct TYPE_7__ {int blocksize; } ;
struct TYPE_6__ {TYPE_2__* cur_decoding_params; } ;
typedef  TYPE_1__ MLPEncodeContext ;
typedef  TYPE_2__ DecodingParams ;
typedef  TYPE_3__ BestOffset ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int HUFF_OFFSET_MAX ; 
 int HUFF_OFFSET_MIN ; 
 int number_sbits (int) ; 

__attribute__((used)) static void no_codebook_bits(MLPEncodeContext *ctx,
                             unsigned int channel,
                             int32_t min, int32_t max,
                             BestOffset *bo)
{
    DecodingParams *dp = ctx->cur_decoding_params;
    int16_t offset;
    int32_t unsign;
    uint32_t diff;
    int lsb_bits;

    /* Set offset inside huffoffset's boundaries by adjusting extremes
     * so that more bits are used, thus shifting the offset. */
    if (min < HUFF_OFFSET_MIN)
        max = FFMAX(max, 2 * HUFF_OFFSET_MIN - min + 1);
    if (max > HUFF_OFFSET_MAX)
        min = FFMIN(min, 2 * HUFF_OFFSET_MAX - max - 1);

    /* Determine offset and minimum number of bits. */
    diff = max - min;

    lsb_bits = number_sbits(diff) - 1;

    unsign = 1 << (lsb_bits - 1);

    /* If all samples are the same (lsb_bits == 0), offset must be
     * adjusted because of sign_shift. */
    offset = min + diff / 2 + !!lsb_bits;

    bo->offset   = offset;
    bo->lsb_bits = lsb_bits;
    bo->bitcount = lsb_bits * dp->blocksize;
    bo->min      = max - unsign + 1;
    bo->max      = min + unsign;
}