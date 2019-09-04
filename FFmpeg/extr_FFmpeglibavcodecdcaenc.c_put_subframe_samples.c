#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int** abits; int** quant_index_sel; scalar_t__*** quantized; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int DCA_CODE_BOOKS ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int* bit_consumption ; 
 int* ff_dca_quant_index_group_size ; 
 int* ff_dca_quant_levels ; 
 int /*<<< orphan*/  ff_dca_vlc_enc_quant (int /*<<< orphan*/ *,scalar_t__*,int,int,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static void put_subframe_samples(DCAEncContext *c, int ss, int band, int ch)
{
    int i, j, sum, bits, sel;
    if (c->abits[ch][band] <= DCA_CODE_BOOKS) {
        av_assert0(c->abits[ch][band] > 0);
        sel = c->quant_index_sel[ch][c->abits[ch][band] - 1];
        // Huffman codes
        if (sel < ff_dca_quant_index_group_size[c->abits[ch][band] - 1]) {
            ff_dca_vlc_enc_quant(&c->pb, &c->quantized[ch][band][ss * 8], 8,
                                 sel, c->abits[ch][band] - 1);
            return;
        }

        // Block codes
        if (c->abits[ch][band] <= 7) {
            for (i = 0; i < 8; i += 4) {
                sum = 0;
                for (j = 3; j >= 0; j--) {
                    sum *= ff_dca_quant_levels[c->abits[ch][band]];
                    sum += c->quantized[ch][band][ss * 8 + i + j];
                    sum += (ff_dca_quant_levels[c->abits[ch][band]] - 1) / 2;
                }
                put_bits(&c->pb, bit_consumption[c->abits[ch][band]] / 4, sum);
            }
            return;
        }
    }

    for (i = 0; i < 8; i++) {
        bits = bit_consumption[c->abits[ch][band]] / 16;
        put_sbits(&c->pb, bits, c->quantized[ch][band][ss * 8 + i]);
    }
}