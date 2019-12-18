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
struct TYPE_3__ {int nb_channels; size_t coeff_per_sb_select; int*** quantized_coeffs; int*** tone_level_idx_base; scalar_t__ superblocktype_2_3; int*** tone_level_idx; int**** tone_level_idx_hi1; int*** tone_level_idx_mid; int** tone_level_idx_hi2; void**** tone_level; int /*<<< orphan*/  sub_sampling; } ;
typedef  TYPE_1__ QDM2Context ;

/* Variables and functions */
 int QDM2_SB_USED (int /*<<< orphan*/ ) ; 
 int** coeff_per_sb_for_dequant ; 
 int*** dequant_table ; 
 void*** fft_tone_level_table ; 
 int* last_coeff ; 

__attribute__((used)) static void fill_tone_level_array(QDM2Context *q, int flag)
{
    int i, sb, ch, sb_used;
    int tmp, tab;

    for (ch = 0; ch < q->nb_channels; ch++)
        for (sb = 0; sb < 30; sb++)
            for (i = 0; i < 8; i++) {
                if ((tab=coeff_per_sb_for_dequant[q->coeff_per_sb_select][sb]) < (last_coeff[q->coeff_per_sb_select] - 1))
                    tmp = q->quantized_coeffs[ch][tab + 1][i] * dequant_table[q->coeff_per_sb_select][tab + 1][sb]+
                          q->quantized_coeffs[ch][tab][i] * dequant_table[q->coeff_per_sb_select][tab][sb];
                else
                    tmp = q->quantized_coeffs[ch][tab][i] * dequant_table[q->coeff_per_sb_select][tab][sb];
                if(tmp < 0)
                    tmp += 0xff;
                q->tone_level_idx_base[ch][sb][i] = (tmp / 256) & 0xff;
            }

    sb_used = QDM2_SB_USED(q->sub_sampling);

    if ((q->superblocktype_2_3 != 0) && !flag) {
        for (sb = 0; sb < sb_used; sb++)
            for (ch = 0; ch < q->nb_channels; ch++)
                for (i = 0; i < 64; i++) {
                    q->tone_level_idx[ch][sb][i] = q->tone_level_idx_base[ch][sb][i / 8];
                    if (q->tone_level_idx[ch][sb][i] < 0)
                        q->tone_level[ch][sb][i] = 0;
                    else
                        q->tone_level[ch][sb][i] = fft_tone_level_table[0][q->tone_level_idx[ch][sb][i] & 0x3f];
                }
    } else {
        tab = q->superblocktype_2_3 ? 0 : 1;
        for (sb = 0; sb < sb_used; sb++) {
            if ((sb >= 4) && (sb <= 23)) {
                for (ch = 0; ch < q->nb_channels; ch++)
                    for (i = 0; i < 64; i++) {
                        tmp = q->tone_level_idx_base[ch][sb][i / 8] -
                              q->tone_level_idx_hi1[ch][sb / 8][i / 8][i % 8] -
                              q->tone_level_idx_mid[ch][sb - 4][i / 8] -
                              q->tone_level_idx_hi2[ch][sb - 4];
                        q->tone_level_idx[ch][sb][i] = tmp & 0xff;
                        if ((tmp < 0) || (!q->superblocktype_2_3 && !tmp))
                            q->tone_level[ch][sb][i] = 0;
                        else
                            q->tone_level[ch][sb][i] = fft_tone_level_table[tab][tmp & 0x3f];
                }
            } else {
                if (sb > 4) {
                    for (ch = 0; ch < q->nb_channels; ch++)
                        for (i = 0; i < 64; i++) {
                            tmp = q->tone_level_idx_base[ch][sb][i / 8] -
                                  q->tone_level_idx_hi1[ch][2][i / 8][i % 8] -
                                  q->tone_level_idx_hi2[ch][sb - 4];
                            q->tone_level_idx[ch][sb][i] = tmp & 0xff;
                            if ((tmp < 0) || (!q->superblocktype_2_3 && !tmp))
                                q->tone_level[ch][sb][i] = 0;
                            else
                                q->tone_level[ch][sb][i] = fft_tone_level_table[tab][tmp & 0x3f];
                    }
                } else {
                    for (ch = 0; ch < q->nb_channels; ch++)
                        for (i = 0; i < 64; i++) {
                            tmp = q->tone_level_idx[ch][sb][i] = q->tone_level_idx_base[ch][sb][i / 8];
                            if ((tmp < 0) || (!q->superblocktype_2_3 && !tmp))
                                q->tone_level[ch][sb][i] = 0;
                            else
                                q->tone_level[ch][sb][i] = fft_tone_level_table[tab][tmp & 0x3f];
                        }
                }
            }
        }
    }
}