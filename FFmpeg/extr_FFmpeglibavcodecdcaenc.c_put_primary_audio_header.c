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
struct TYPE_3__ {int fullband_channels; int* bit_allocation_sel; int** quant_index_sel; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int DCAENC_SUBBANDS ; 
 int DCA_CODE_BOOKS ; 
 int SUBFRAMES ; 
 int* ff_dca_quant_index_group_size ; 
 int* ff_dca_quant_index_sel_nbits ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void put_primary_audio_header(DCAEncContext *c)
{
    int ch, i;
    /* Number of subframes */
    put_bits(&c->pb, 4, SUBFRAMES - 1);

    /* Number of primary audio channels */
    put_bits(&c->pb, 3, c->fullband_channels - 1);

    /* Subband activity count */
    for (ch = 0; ch < c->fullband_channels; ch++)
        put_bits(&c->pb, 5, DCAENC_SUBBANDS - 2);

    /* High frequency VQ start subband */
    for (ch = 0; ch < c->fullband_channels; ch++)
        put_bits(&c->pb, 5, DCAENC_SUBBANDS - 1);

    /* Joint intensity coding index: 0, 0 */
    for (ch = 0; ch < c->fullband_channels; ch++)
        put_bits(&c->pb, 3, 0);

    /* Transient mode codebook: A4, A4 (arbitrary) */
    for (ch = 0; ch < c->fullband_channels; ch++)
        put_bits(&c->pb, 2, 0);

    /* Scale factor code book: 7 bit linear, 7-bit sqrt table (for each channel) */
    for (ch = 0; ch < c->fullband_channels; ch++)
        put_bits(&c->pb, 3, 6);

    /* Bit allocation quantizer select: linear 5-bit */
    for (ch = 0; ch < c->fullband_channels; ch++)
        put_bits(&c->pb, 3, c->bit_allocation_sel[ch]);

    /* Quantization index codebook select */
    for (i = 0; i < DCA_CODE_BOOKS; i++)
        for (ch = 0; ch < c->fullband_channels; ch++)
            put_bits(&c->pb, ff_dca_quant_index_sel_nbits[i], c->quant_index_sel[ch][i]);

    /* Scale factor adjustment index: transmitted in case of Huffman coding */
    for (i = 0; i < DCA_CODE_BOOKS; i++)
        for (ch = 0; ch < c->fullband_channels; ch++)
            if (c->quant_index_sel[ch][i] < ff_dca_quant_index_group_size[i])
                put_bits(&c->pb, 2, 0);

    /* Audio header CRC check word: not transmitted */
}