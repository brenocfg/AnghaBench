#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_5__ {int* k; int* kx; int sample_rate; int num_patches; int* m; int* f_master; int n_master; int* patch_num_subbands; int* patch_start_subband; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  TYPE_2__ AACContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int sbr_hf_calc_npatches(AACContext *ac, SpectralBandReplication *sbr)
{
    int i, k, last_k = -1, last_msb = -1, sb = 0;
    int msb = sbr->k[0];
    int usb = sbr->kx[1];
    int goal_sb = ((1000 << 11) + (sbr->sample_rate >> 1)) / sbr->sample_rate;

    sbr->num_patches = 0;

    if (goal_sb < sbr->kx[1] + sbr->m[1]) {
        for (k = 0; sbr->f_master[k] < goal_sb; k++) ;
    } else
        k = sbr->n_master;

    do {
        int odd = 0;
        if (k == last_k && msb == last_msb) {
            av_log(ac->avctx, AV_LOG_ERROR, "patch construction failed\n");
            return AVERROR_INVALIDDATA;
        }
        last_k = k;
        last_msb = msb;
        for (i = k; i == k || sb > (sbr->k[0] - 1 + msb - odd); i--) {
            sb = sbr->f_master[i];
            odd = (sb + sbr->k[0]) & 1;
        }

        // Requirements (14496-3 sp04 p205) sets the maximum number of patches to 5.
        // After this check the final number of patches can still be six which is
        // illegal however the Coding Technologies decoder check stream has a final
        // count of 6 patches
        if (sbr->num_patches > 5) {
            av_log(ac->avctx, AV_LOG_ERROR, "Too many patches: %d\n", sbr->num_patches);
            return -1;
        }

        sbr->patch_num_subbands[sbr->num_patches]  = FFMAX(sb - usb, 0);
        sbr->patch_start_subband[sbr->num_patches] = sbr->k[0] - odd - sbr->patch_num_subbands[sbr->num_patches];

        if (sbr->patch_num_subbands[sbr->num_patches] > 0) {
            usb = sb;
            msb = sb;
            sbr->num_patches++;
        } else
            msb = sbr->kx[1];

        if (sbr->f_master[k] - sb < 3)
            k = sbr->n_master;
    } while (sb != sbr->kx[1] + sbr->m[1]);

    if (sbr->num_patches > 1 &&
        sbr->patch_num_subbands[sbr->num_patches - 1] < 3)
        sbr->num_patches--;

    return 0;
}