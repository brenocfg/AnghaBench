#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* hf_gen ) (int /*<<< orphan*/ **,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int,int) ;} ;
struct TYPE_7__ {int* kx; int num_patches; int* patch_num_subbands; int* patch_start_subband; int n_q; int* f_tablenoise; int* m; TYPE_1__ dsp; } ;
typedef  TYPE_2__ SpectralBandReplication ;
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  TYPE_3__ AACContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int ENVELOPE_ADJUSTMENT_OFFSET ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ***,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int,int) ; 

__attribute__((used)) static int sbr_hf_gen(AACContext *ac, SpectralBandReplication *sbr,
                      INTFLOAT X_high[64][40][2], const INTFLOAT X_low[32][40][2],
                      const INTFLOAT (*alpha0)[2], const INTFLOAT (*alpha1)[2],
                      const INTFLOAT bw_array[5], const uint8_t *t_env,
                      int bs_num_env)
{
    int j, x;
    int g = 0;
    int k = sbr->kx[1];
    for (j = 0; j < sbr->num_patches; j++) {
        for (x = 0; x < sbr->patch_num_subbands[j]; x++, k++) {
            const int p = sbr->patch_start_subband[j] + x;
            while (g <= sbr->n_q && k >= sbr->f_tablenoise[g])
                g++;
            g--;

            if (g < 0) {
                av_log(ac->avctx, AV_LOG_ERROR,
                       "ERROR : no subband found for frequency %d\n", k);
                return -1;
            }

            sbr->dsp.hf_gen(X_high[k] + ENVELOPE_ADJUSTMENT_OFFSET,
                            X_low[p]  + ENVELOPE_ADJUSTMENT_OFFSET,
                            alpha0[p], alpha1[p], bw_array[g],
                            2 * t_env[0], 2 * t_env[bs_num_env]);
        }
    }
    if (k < sbr->m[1] + sbr->kx[1])
        memset(X_high + k, 0, (sbr->m[1] + sbr->kx[1] - k) * sizeof(*X_high));

    return 0;
}