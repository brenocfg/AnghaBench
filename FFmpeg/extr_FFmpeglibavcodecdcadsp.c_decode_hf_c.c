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
typedef  size_t int8_t ;
typedef  size_t int32_t ;

/* Variables and functions */
 size_t clip23 (size_t const) ; 

__attribute__((used)) static void decode_hf_c(int32_t **dst,
                        const int32_t *vq_index,
                        const int8_t hf_vq[1024][32],
                        int32_t scale_factors[32][2],
                        ptrdiff_t sb_start, ptrdiff_t sb_end,
                        ptrdiff_t ofs, ptrdiff_t len)
{
    int i, j;

    for (i = sb_start; i < sb_end; i++) {
        const int8_t *coeff = hf_vq[vq_index[i]];
        int32_t scale = scale_factors[i][0];
        for (j = 0; j < len; j++)
            dst[i][j + ofs] = clip23(coeff[j] * scale + (1 << 3) >> 4);
    }
}