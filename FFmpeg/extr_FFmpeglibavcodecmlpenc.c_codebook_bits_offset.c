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
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_8__ {int lsb_bits; int bitcount; int /*<<< orphan*/  max; int /*<<< orphan*/  min; scalar_t__ offset; } ;
struct TYPE_7__ {int blocksize; scalar_t__* quant_step_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_channels; TYPE_2__* cur_decoding_params; scalar_t__* sample_buffer; } ;
typedef  TYPE_1__ MLPEncodeContext ;
typedef  TYPE_2__ DecodingParams ;
typedef  TYPE_3__ BestOffset ;

/* Variables and functions */
 int /*<<< orphan*/  FFMAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFMIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUFF_OFFSET_MAX ; 
 int /*<<< orphan*/  HUFF_OFFSET_MIN ; 
 int INT_MAX ; 
 scalar_t__** codebook_extremes ; 
 scalar_t__*** ff_mlp_huffman_tables ; 

__attribute__((used)) static inline void codebook_bits_offset(MLPEncodeContext *ctx,
                                        unsigned int channel, int codebook,
                                        int32_t sample_min, int32_t sample_max,
                                        int16_t offset, BestOffset *bo)
{
    int32_t codebook_min = codebook_extremes[codebook][0];
    int32_t codebook_max = codebook_extremes[codebook][1];
    int32_t *sample_buffer = ctx->sample_buffer + channel;
    DecodingParams *dp = ctx->cur_decoding_params;
    int codebook_offset  = 7 + (2 - codebook);
    int32_t unsign_offset = offset;
    int lsb_bits = 0, bitcount = 0;
    int offset_min = INT_MAX, offset_max = INT_MAX;
    int unsign, mask;
    int i;

    sample_min -= offset;
    sample_max -= offset;

    while (sample_min < codebook_min || sample_max > codebook_max) {
        lsb_bits++;
        sample_min >>= 1;
        sample_max >>= 1;
    }

    unsign = 1 << lsb_bits;
    mask   = unsign - 1;

    if (codebook == 2) {
        unsign_offset -= unsign;
        lsb_bits++;
    }

    for (i = 0; i < dp->blocksize; i++) {
        int32_t sample = *sample_buffer >> dp->quant_step_size[channel];
        int temp_min, temp_max;

        sample -= unsign_offset;

        temp_min = sample & mask;
        if (temp_min < offset_min)
            offset_min = temp_min;

        temp_max = unsign - temp_min - 1;
        if (temp_max < offset_max)
            offset_max = temp_max;

        sample >>= lsb_bits;

        bitcount += ff_mlp_huffman_tables[codebook][sample + codebook_offset][1];

        sample_buffer += ctx->num_channels;
    }

    bo->offset   = offset;
    bo->lsb_bits = lsb_bits;
    bo->bitcount = lsb_bits * dp->blocksize + bitcount;
    bo->min      = FFMAX(offset - offset_min, HUFF_OFFSET_MIN);
    bo->max      = FFMIN(offset + offset_max, HUFF_OFFSET_MAX);
}