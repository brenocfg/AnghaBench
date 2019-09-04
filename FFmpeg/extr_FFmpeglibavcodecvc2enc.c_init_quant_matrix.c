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
struct TYPE_3__ {int wavelet_depth; scalar_t__ quant_matrix; int custom_quant_matrix; size_t wavelet_idx; void*** quant; } ;
typedef  TYPE_1__ VC2EncContext ;

/* Variables and functions */
 scalar_t__ VC2_QM_COL ; 
 scalar_t__ VC2_QM_DEF ; 
 void**** ff_dirac_default_qmat ; 
 void*** vc2_qm_col_tab ; 
 void*** vc2_qm_flat_tab ; 

__attribute__((used)) static void init_quant_matrix(VC2EncContext *s)
{
    int level, orientation;

    if (s->wavelet_depth <= 4 && s->quant_matrix == VC2_QM_DEF) {
        s->custom_quant_matrix = 0;
        for (level = 0; level < s->wavelet_depth; level++) {
            s->quant[level][0] = ff_dirac_default_qmat[s->wavelet_idx][level][0];
            s->quant[level][1] = ff_dirac_default_qmat[s->wavelet_idx][level][1];
            s->quant[level][2] = ff_dirac_default_qmat[s->wavelet_idx][level][2];
            s->quant[level][3] = ff_dirac_default_qmat[s->wavelet_idx][level][3];
        }
        return;
    }

    s->custom_quant_matrix = 1;

    if (s->quant_matrix == VC2_QM_DEF) {
        for (level = 0; level < s->wavelet_depth; level++) {
            for (orientation = 0; orientation < 4; orientation++) {
                if (level <= 3)
                    s->quant[level][orientation] = ff_dirac_default_qmat[s->wavelet_idx][level][orientation];
                else
                    s->quant[level][orientation] = vc2_qm_col_tab[level][orientation];
            }
        }
    } else if (s->quant_matrix == VC2_QM_COL) {
        for (level = 0; level < s->wavelet_depth; level++) {
            for (orientation = 0; orientation < 4; orientation++) {
                s->quant[level][orientation] = vc2_qm_col_tab[level][orientation];
            }
        }
    } else {
        for (level = 0; level < s->wavelet_depth; level++) {
            for (orientation = 0; orientation < 4; orientation++) {
                s->quant[level][orientation] = vc2_qm_flat_tab[level][orientation];
            }
        }
    }
}