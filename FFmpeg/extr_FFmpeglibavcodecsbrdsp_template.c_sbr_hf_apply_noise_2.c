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
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  int /*<<< orphan*/  AAC_FLOAT ;

/* Variables and functions */
 int /*<<< orphan*/  sbr_hf_apply_noise (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sbr_hf_apply_noise_2(INTFLOAT (*Y)[2], const AAC_FLOAT *s_m,
                                 const AAC_FLOAT *q_filt, int noise,
                                 int kx, int m_max)
{
    sbr_hf_apply_noise(Y, s_m, q_filt, noise, (INTFLOAT)-1.0, (INTFLOAT)0.0, m_max);
}