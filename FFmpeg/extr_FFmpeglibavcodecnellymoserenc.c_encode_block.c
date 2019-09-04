#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float* mdct_out; TYPE_1__* avctx; } ;
struct TYPE_7__ {scalar_t__ trellis; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_2__ NellyMoserEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMAX (double,float) ; 
 int NELLY_BANDS ; 
 int NELLY_BUF_LEN ; 
 int NELLY_DETAIL_BITS ; 
 int NELLY_FILL_LEN ; 
 int NELLY_HEADER_BITS ; 
 int POW_TABLE_OFFSET ; 
 int /*<<< orphan*/  apply_mdct (TYPE_2__*) ; 
 size_t av_clip (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fabs (float) ; 
 int* ff_nelly_band_sizes_table ; 
 scalar_t__* ff_nelly_delta_table ; 
 float* ff_nelly_dequantization_table ; 
 int /*<<< orphan*/  ff_nelly_get_sample_bits (float*,int*) ; 
 int* ff_nelly_init_table ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_exponent_dynamic (TYPE_2__*,float*,int*) ; 
 int /*<<< orphan*/  get_exponent_greedy (TYPE_2__*,float*,int*) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,unsigned char*,int) ; 
 double log2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,unsigned char*) ; 
 int* pow_table ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int put_bits_ptr (int /*<<< orphan*/ *) ; 
 int* quant_lut ; 
 scalar_t__* quant_lut_add ; 
 float* quant_lut_mul ; 
 scalar_t__* quant_lut_offset ; 

__attribute__((used)) static void encode_block(NellyMoserEncodeContext *s, unsigned char *output, int output_size)
{
    PutBitContext pb;
    int i, j, band, block, best_idx, power_idx = 0;
    float power_val, coeff, coeff_sum;
    float pows[NELLY_FILL_LEN];
    int bits[NELLY_BUF_LEN], idx_table[NELLY_BANDS];
    float cand[NELLY_BANDS];

    apply_mdct(s);

    init_put_bits(&pb, output, output_size);

    i = 0;
    for (band = 0; band < NELLY_BANDS; band++) {
        coeff_sum = 0;
        for (j = 0; j < ff_nelly_band_sizes_table[band]; i++, j++) {
            coeff_sum += s->mdct_out[i                ] * s->mdct_out[i                ]
                       + s->mdct_out[i + NELLY_BUF_LEN] * s->mdct_out[i + NELLY_BUF_LEN];
        }
        cand[band] =
            log2(FFMAX(1.0, coeff_sum / (ff_nelly_band_sizes_table[band] << 7))) * 1024.0;
    }

    if (s->avctx->trellis) {
        get_exponent_dynamic(s, cand, idx_table);
    } else {
        get_exponent_greedy(s, cand, idx_table);
    }

    i = 0;
    for (band = 0; band < NELLY_BANDS; band++) {
        if (band) {
            power_idx += ff_nelly_delta_table[idx_table[band]];
            put_bits(&pb, 5, idx_table[band]);
        } else {
            power_idx = ff_nelly_init_table[idx_table[0]];
            put_bits(&pb, 6, idx_table[0]);
        }
        power_val = pow_table[power_idx & 0x7FF] / (1 << ((power_idx >> 11) + POW_TABLE_OFFSET));
        for (j = 0; j < ff_nelly_band_sizes_table[band]; i++, j++) {
            s->mdct_out[i] *= power_val;
            s->mdct_out[i + NELLY_BUF_LEN] *= power_val;
            pows[i] = power_idx;
        }
    }

    ff_nelly_get_sample_bits(pows, bits);

    for (block = 0; block < 2; block++) {
        for (i = 0; i < NELLY_FILL_LEN; i++) {
            if (bits[i] > 0) {
                const float *table = ff_nelly_dequantization_table + (1 << bits[i]) - 1;
                coeff = s->mdct_out[block * NELLY_BUF_LEN + i];
                best_idx =
                    quant_lut[av_clip (
                            coeff * quant_lut_mul[bits[i]] + quant_lut_add[bits[i]],
                            quant_lut_offset[bits[i]],
                            quant_lut_offset[bits[i]+1] - 1
                            )];
                if (fabs(coeff - table[best_idx]) > fabs(coeff - table[best_idx + 1]))
                    best_idx++;

                put_bits(&pb, bits[i], best_idx);
            }
        }
        if (!block)
            put_bits(&pb, NELLY_HEADER_BITS + NELLY_DETAIL_BITS - put_bits_count(&pb), 0);
    }

    flush_put_bits(&pb);
    memset(put_bits_ptr(&pb), 0, output + output_size - put_bits_ptr(&pb));
}