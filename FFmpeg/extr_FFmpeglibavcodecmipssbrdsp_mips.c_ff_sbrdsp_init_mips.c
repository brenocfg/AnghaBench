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
typedef  int /*<<< orphan*/  SBRDSPContext ;

/* Variables and functions */

void ff_sbrdsp_init_mips(SBRDSPContext *s)
{
#if HAVE_INLINE_ASM
    s->qmf_pre_shuffle = sbr_qmf_pre_shuffle_mips;
    s->qmf_post_shuffle = sbr_qmf_post_shuffle_mips;
#if HAVE_MIPSFPU
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    s->sum64x5 = sbr_sum64x5_mips;
    s->sum_square = sbr_sum_square_mips;
    s->qmf_deint_bfly = sbr_qmf_deint_bfly_mips;
    s->autocorrelate = sbr_autocorrelate_mips;
    s->hf_gen = sbr_hf_gen_mips;
    s->hf_g_filt = sbr_hf_g_filt_mips;

    s->hf_apply_noise[0] = sbr_hf_apply_noise_0_mips;
    s->hf_apply_noise[1] = sbr_hf_apply_noise_1_mips;
    s->hf_apply_noise[2] = sbr_hf_apply_noise_2_mips;
    s->hf_apply_noise[3] = sbr_hf_apply_noise_3_mips;
#endif /* !HAVE_MIPS32R6 && !HAVE_MIPS64R6 */
#endif /* HAVE_MIPSFPU */
#endif /* HAVE_INLINE_ASM */
}