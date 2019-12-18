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
struct TYPE_3__ {int* coded_ac_scale_factor; size_t* qps; int** coded_dc_scale_factor; int** qr_count; int*** qr_size; int*** qr_base; int** base_matrix; int**** qmat; size_t* idct_permutation; int version; } ;
typedef  TYPE_1__ Vp3DecodeContext ;

/* Variables and functions */
 int av_clip (int,int,int) ; 

__attribute__((used)) static void init_dequantizer(Vp3DecodeContext *s, int qpi)
{
    int ac_scale_factor = s->coded_ac_scale_factor[s->qps[qpi]];
    int i, plane, inter, qri, bmi, bmj, qistart;

    for (inter = 0; inter < 2; inter++) {
        for (plane = 0; plane < 3; plane++) {
            int dc_scale_factor = s->coded_dc_scale_factor[!!plane][s->qps[qpi]];
            int sum = 0;
            for (qri = 0; qri < s->qr_count[inter][plane]; qri++) {
                sum += s->qr_size[inter][plane][qri];
                if (s->qps[qpi] <= sum)
                    break;
            }
            qistart = sum - s->qr_size[inter][plane][qri];
            bmi     = s->qr_base[inter][plane][qri];
            bmj     = s->qr_base[inter][plane][qri + 1];
            for (i = 0; i < 64; i++) {
                int coeff = (2 * (sum     - s->qps[qpi]) * s->base_matrix[bmi][i] -
                             2 * (qistart - s->qps[qpi]) * s->base_matrix[bmj][i] +
                             s->qr_size[inter][plane][qri]) /
                            (2 * s->qr_size[inter][plane][qri]);

                int qmin   = 8 << (inter + !i);
                int qscale = i ? ac_scale_factor : dc_scale_factor;
                int qbias = (1 + inter) * 3;
                s->qmat[qpi][inter][plane][s->idct_permutation[i]] =
                    (i == 0 || s->version < 2) ? av_clip((qscale * coeff) / 100 * 4, qmin, 4096)
                                               : (qscale * (coeff - qbias) / 100 + qbias) * 4;
            }
            /* all DC coefficients use the same quant so as not to interfere
             * with DC prediction */
            s->qmat[qpi][inter][plane][0] = s->qmat[0][inter][plane][0];
        }
    }
}