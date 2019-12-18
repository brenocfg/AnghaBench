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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  lfe_fir_float_c (float*,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lfe_fir1_float_c(float *pcm_samples, int32_t *lfe_samples,
                             const float *filter_coeff, ptrdiff_t npcmblocks)
{
    lfe_fir_float_c(pcm_samples, lfe_samples, filter_coeff, npcmblocks, 1);
}