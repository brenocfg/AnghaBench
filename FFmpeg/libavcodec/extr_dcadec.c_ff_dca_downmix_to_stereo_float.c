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
struct TYPE_3__ {int /*<<< orphan*/  (* vector_fmac_scalar ) (float*,float*,int,int) ;int /*<<< orphan*/  (* vector_fmul_scalar ) (float*,float*,int,int) ;} ;
typedef  TYPE_1__ AVFloatDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  DCA_HAS_STEREO (int) ; 
 size_t DCA_SPEAKER_L ; 
 int DCA_SPEAKER_MASK_C ; 
 size_t DCA_SPEAKER_R ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int av_log2 (int) ; 
 int av_popcount (int) ; 
 int /*<<< orphan*/  stub1 (float*,float*,int,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,int,int) ; 
 int /*<<< orphan*/  stub3 (float*,float*,int,int) ; 
 int /*<<< orphan*/  stub4 (float*,float*,int,int) ; 

void ff_dca_downmix_to_stereo_float(AVFloatDSPContext *fdsp, float **samples,
                                    int *coeff_l, int nsamples, int ch_mask)
{
    int pos, spkr, max_spkr = av_log2(ch_mask);
    int *coeff_r = coeff_l + av_popcount(ch_mask);
    const float scale = 1.0f / (1 << 15);

    av_assert0(DCA_HAS_STEREO(ch_mask));

    // Scale left and right channels
    pos = (ch_mask & DCA_SPEAKER_MASK_C);
    fdsp->vector_fmul_scalar(samples[DCA_SPEAKER_L], samples[DCA_SPEAKER_L],
                             coeff_l[pos    ] * scale, nsamples);
    fdsp->vector_fmul_scalar(samples[DCA_SPEAKER_R], samples[DCA_SPEAKER_R],
                             coeff_r[pos + 1] * scale, nsamples);

    // Downmix remaining channels
    for (spkr = 0; spkr <= max_spkr; spkr++) {
        if (!(ch_mask & (1U << spkr)))
            continue;

        if (*coeff_l && spkr != DCA_SPEAKER_L)
            fdsp->vector_fmac_scalar(samples[DCA_SPEAKER_L], samples[spkr],
                                     *coeff_l * scale, nsamples);

        if (*coeff_r && spkr != DCA_SPEAKER_R)
            fdsp->vector_fmac_scalar(samples[DCA_SPEAKER_R], samples[spkr],
                                     *coeff_r * scale, nsamples);

        coeff_l++;
        coeff_r++;
    }
}