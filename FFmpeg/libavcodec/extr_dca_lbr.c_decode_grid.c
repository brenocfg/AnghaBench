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
typedef  int uint8_t ;
typedef  int int8_t ;
struct TYPE_3__ {int nsubbands; int*** grid_1_scf; int*** high_res_scf; int*** grid_3_scf; int** grid_3_avg; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 int** ff_dca_grid_1_weights ; 
 int* ff_dca_scf_to_grid_1 ; 

__attribute__((used)) static void decode_grid(DCALbrDecoder *s, int ch1, int ch2)
{
    int i, ch, sb;

    for (ch = ch1; ch <= ch2; ch++) {
        for (sb = 0; sb < s->nsubbands; sb++) {
            int g1_sb = ff_dca_scf_to_grid_1[sb];

            uint8_t *g1_scf_a = s->grid_1_scf[ch][g1_sb    ];
            uint8_t *g1_scf_b = s->grid_1_scf[ch][g1_sb + 1];

            int w1 = ff_dca_grid_1_weights[g1_sb    ][sb];
            int w2 = ff_dca_grid_1_weights[g1_sb + 1][sb];

            uint8_t *hr_scf = s->high_res_scf[ch][sb];

            if (sb < 4) {
                for (i = 0; i < 8; i++) {
                    int scf = w1 * g1_scf_a[i] + w2 * g1_scf_b[i];
                    hr_scf[i] = scf >> 7;
                }
            } else {
                int8_t *g3_scf = s->grid_3_scf[ch][sb - 4];
                int g3_avg = s->grid_3_avg[ch][sb - 4];

                for (i = 0; i < 8; i++) {
                    int scf = w1 * g1_scf_a[i] + w2 * g1_scf_b[i];
                    hr_scf[i] = (scf >> 7) - g3_avg - g3_scf[i];
                }
            }
        }
    }
}