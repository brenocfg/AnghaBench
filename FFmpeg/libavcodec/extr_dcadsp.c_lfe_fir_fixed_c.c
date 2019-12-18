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
typedef  int ptrdiff_t ;
typedef  int int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int clip23 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  norm23 (int) ; 

__attribute__((used)) static void lfe_fir_fixed_c(int32_t *pcm_samples, int32_t *lfe_samples,
                            const int32_t *filter_coeff, ptrdiff_t npcmblocks)
{
    // Select decimation factor
    int nlfesamples = npcmblocks >> 1;
    int i, j, k;

    for (i = 0; i < nlfesamples; i++) {
        // One decimated sample generates 64 interpolated ones
        for (j = 0; j < 32; j++) {
            int64_t a = 0;
            int64_t b = 0;

            for (k = 0; k < 8; k++) {
                a += (int64_t)filter_coeff[      j * 8 + k] * lfe_samples[-k];
                b += (int64_t)filter_coeff[255 - j * 8 - k] * lfe_samples[-k];
            }

            pcm_samples[     j] = clip23(norm23(a));
            pcm_samples[32 + j] = clip23(norm23(b));
        }

        lfe_samples++;
        pcm_samples += 64;
    }
}