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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int consumed_bits; int fullband_channels; int** peak_cb; int* band_masking_cb; int** abits; int** prediction_mode; int /*<<< orphan*/ * quant_index_sel; int /*<<< orphan*/ ** quantized; int /*<<< orphan*/ ** quant; int /*<<< orphan*/ ** scale_factor; int /*<<< orphan*/ * bit_allocation_sel; scalar_t__ lfe_channel; scalar_t__ consumed_adpcm_bits; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int DCA_CODE_BOOKS ; 
 int MAX_CHANNELS ; 
 int USED_1ABITS ; 
 int USED_26ABITS ; 
 int /*<<< orphan*/  accumulate_huff_bit_consumption (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__* bit_consumption ; 
 int /*<<< orphan*/  calc_one_scale (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__**,int /*<<< orphan*/ ,int) ; 
 void* mul32 (int,int) ; 
 int /*<<< orphan*/  quantize_adpcm (TYPE_1__*) ; 
 int /*<<< orphan*/  quantize_pcm (TYPE_1__*) ; 
 scalar_t__ set_best_abits_code (int*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ set_best_code (scalar_t__**,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_quantization_noise(DCAEncContext *c, int noise, int forbid_zero)
{
    int ch, band, ret = USED_26ABITS | USED_1ABITS;
    uint32_t huff_bit_count_accum[MAX_CHANNELS][DCA_CODE_BOOKS][7];
    uint32_t clc_bit_count_accum[MAX_CHANNELS][DCA_CODE_BOOKS];
    uint32_t bits_counter = 0;

    c->consumed_bits = 132 + 333 * c->fullband_channels;
    c->consumed_bits += c->consumed_adpcm_bits;
    if (c->lfe_channel)
        c->consumed_bits += 72;

    /* attempt to guess the bit distribution based on the prevoius frame */
    for (ch = 0; ch < c->fullband_channels; ch++) {
        for (band = 0; band < 32; band++) {
            int snr_cb = c->peak_cb[ch][band] - c->band_masking_cb[band] - noise;

            if (snr_cb >= 1312) {
                c->abits[ch][band] = 26;
                ret &= ~USED_1ABITS;
            } else if (snr_cb >= 222) {
                c->abits[ch][band] = 8 + mul32(snr_cb - 222, 69000000);
                ret &= ~(USED_26ABITS | USED_1ABITS);
            } else if (snr_cb >= 0) {
                c->abits[ch][band] = 2 + mul32(snr_cb, 106000000);
                ret &= ~(USED_26ABITS | USED_1ABITS);
            } else if (forbid_zero || snr_cb >= -140) {
                c->abits[ch][band] = 1;
                ret &= ~USED_26ABITS;
            } else {
                c->abits[ch][band] = 0;
                ret &= ~(USED_26ABITS | USED_1ABITS);
            }
        }
        c->consumed_bits += set_best_abits_code(c->abits[ch], 32,
                                                &c->bit_allocation_sel[ch]);
    }

    /* Recalc scale_factor each time to get bits consumption in case of Huffman coding.
       It is suboptimal solution */
    /* TODO: May be cache scaled values */
    for (ch = 0; ch < c->fullband_channels; ch++) {
        for (band = 0; band < 32; band++) {
            if (c->prediction_mode[ch][band] == -1) {
                c->scale_factor[ch][band] = calc_one_scale(c, c->peak_cb[ch][band],
                                                           c->abits[ch][band],
                                                           &c->quant[ch][band]);
            }
        }
    }
    quantize_adpcm(c);
    quantize_pcm(c);

    memset(huff_bit_count_accum, 0, MAX_CHANNELS * DCA_CODE_BOOKS * 7 * sizeof(uint32_t));
    memset(clc_bit_count_accum, 0, MAX_CHANNELS * DCA_CODE_BOOKS * sizeof(uint32_t));
    for (ch = 0; ch < c->fullband_channels; ch++) {
        for (band = 0; band < 32; band++) {
            if (c->abits[ch][band] && c->abits[ch][band] <= DCA_CODE_BOOKS) {
                accumulate_huff_bit_consumption(c->abits[ch][band],
                                                c->quantized[ch][band],
                                                huff_bit_count_accum[ch][c->abits[ch][band] - 1]);
                clc_bit_count_accum[ch][c->abits[ch][band] - 1] += bit_consumption[c->abits[ch][band]];
            } else {
                bits_counter += bit_consumption[c->abits[ch][band]];
            }
        }
    }

    for (ch = 0; ch < c->fullband_channels; ch++) {
        bits_counter += set_best_code(huff_bit_count_accum[ch],
                                      clc_bit_count_accum[ch],
                                      c->quant_index_sel[ch]);
    }

    c->consumed_bits += bits_counter;

    return ret;
}