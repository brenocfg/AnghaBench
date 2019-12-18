#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int DCA_CODE_BOOKS ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int* ff_dca_quant_index_group_size ; 

__attribute__((used)) static uint32_t set_best_code(uint32_t vlc_bits[DCA_CODE_BOOKS][7],
                              uint32_t clc_bits[DCA_CODE_BOOKS],
                              int32_t res[DCA_CODE_BOOKS])
{
    uint8_t i, sel;
    uint32_t best_sel_bits[DCA_CODE_BOOKS];
    int32_t best_sel_id[DCA_CODE_BOOKS];
    uint32_t t, bits = 0;

    for (i = 0; i < DCA_CODE_BOOKS; i++) {

        av_assert0(!((!!vlc_bits[i][0]) ^ (!!clc_bits[i])));
        if (vlc_bits[i][0] == 0) {
            /* do not transmit adjustment index for empty codebooks */
            res[i] = ff_dca_quant_index_group_size[i];
            /* and skip it */
            continue;
        }

        best_sel_bits[i] = vlc_bits[i][0];
        best_sel_id[i] = 0;
        for (sel = 0; sel < ff_dca_quant_index_group_size[i]; sel++) {
            if (best_sel_bits[i] > vlc_bits[i][sel] && vlc_bits[i][sel]) {
                best_sel_bits[i] = vlc_bits[i][sel];
                best_sel_id[i] = sel;
            }
        }

        /* 2 bits to transmit scale factor adjustment index */
        t = best_sel_bits[i] + 2;
        if (t < clc_bits[i]) {
            res[i] = best_sel_id[i];
            bits += t;
        } else {
            res[i] = ff_dca_quant_index_group_size[i];
            bits += clc_bits[i];
        }
    }
    return bits;
}