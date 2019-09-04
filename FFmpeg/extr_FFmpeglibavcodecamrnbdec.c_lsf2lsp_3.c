#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  double int16_t ;
struct TYPE_4__ {size_t* lsf; } ;
struct TYPE_5__ {scalar_t__ cur_frame_mode; double* prev_lsf_r; double** lsp; double* prev_lsp_sub4; int /*<<< orphan*/  lsf_q; int /*<<< orphan*/  acelpv_ctx; TYPE_1__ frame; } ;
typedef  TYPE_2__ AMRContext ;

/* Variables and functions */
 int LP_FILTER_ORDER ; 
 double LSF_R_FAC ; 
 int /*<<< orphan*/  MIN_LSF_SPACING ; 
 scalar_t__ MODE_5k15 ; 
 scalar_t__ MODE_7k95 ; 
 int /*<<< orphan*/  ff_acelp_lsf2lspd (double*,float*,int) ; 
 int /*<<< orphan*/  ff_set_min_dist_lsf (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  interpolate_lsf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 
 double** lsf_3_1 ; 
 double** lsf_3_1_MODE_7k95 ; 
 double** lsf_3_2 ; 
 double** lsf_3_3 ; 
 double** lsf_3_3_MODE_5k15 ; 
 double* lsf_3_mean ; 
 int /*<<< orphan*/  memcpy (double*,double const*,int) ; 
 double* pred_fac ; 

__attribute__((used)) static void lsf2lsp_3(AMRContext *p)
{
    const uint16_t *lsf_param = p->frame.lsf;
    int16_t lsf_r[LP_FILTER_ORDER]; // residual LSF vector
    float lsf_q[LP_FILTER_ORDER]; // quantified LSF vector
    const int16_t *lsf_quantizer;
    int i, j;

    lsf_quantizer = (p->cur_frame_mode == MODE_7k95 ? lsf_3_1_MODE_7k95 : lsf_3_1)[lsf_param[0]];
    memcpy(lsf_r, lsf_quantizer, 3 * sizeof(*lsf_r));

    lsf_quantizer = lsf_3_2[lsf_param[1] << (p->cur_frame_mode <= MODE_5k15)];
    memcpy(lsf_r + 3, lsf_quantizer, 3 * sizeof(*lsf_r));

    lsf_quantizer = (p->cur_frame_mode <= MODE_5k15 ? lsf_3_3_MODE_5k15 : lsf_3_3)[lsf_param[2]];
    memcpy(lsf_r + 6, lsf_quantizer, 4 * sizeof(*lsf_r));

    // calculate mean-removed LSF vector and add mean
    for (i = 0; i < LP_FILTER_ORDER; i++)
        lsf_q[i] = (lsf_r[i] + p->prev_lsf_r[i] * pred_fac[i]) * (LSF_R_FAC / 8000.0) + lsf_3_mean[i] * (1.0 / 8000.0);

    ff_set_min_dist_lsf(lsf_q, MIN_LSF_SPACING, LP_FILTER_ORDER);

    // store data for computing the next frame's LSFs
    interpolate_lsf(&p->acelpv_ctx, p->lsf_q, lsf_q);
    memcpy(p->prev_lsf_r, lsf_r, LP_FILTER_ORDER * sizeof(*lsf_r));

    ff_acelp_lsf2lspd(p->lsp[3], lsf_q, LP_FILTER_ORDER);

    // interpolate LSP vectors at subframes 1, 2 and 3
    for (i = 1; i <= 3; i++)
        for(j = 0; j < LP_FILTER_ORDER; j++)
            p->lsp[i-1][j] = p->prev_lsp_sub4[j] +
                (p->lsp[3][j] - p->prev_lsp_sub4[j]) * 0.25 * i;
}