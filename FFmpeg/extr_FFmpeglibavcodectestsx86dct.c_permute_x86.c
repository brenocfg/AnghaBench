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
typedef  int /*<<< orphan*/  int16_t ;
typedef  enum idct_permutation_type { ____Placeholder_idct_permutation_type } idct_permutation_type ;

/* Variables and functions */
#define  FF_IDCT_PERM_SIMPLE 129 
#define  FF_IDCT_PERM_SSE2 128 
 size_t* idct_simple_mmx_perm ; 
 int* idct_sse2_row_perm ; 

__attribute__((used)) static int permute_x86(int16_t dst[64], const int16_t src[64],
                       enum idct_permutation_type perm_type)
{
    int i;

    switch (perm_type) {
    case FF_IDCT_PERM_SIMPLE:
        for (i = 0; i < 64; i++)
            dst[idct_simple_mmx_perm[i]] = src[i];
        return 1;
    case FF_IDCT_PERM_SSE2:
        for (i = 0; i < 64; i++)
            dst[(i & 0x38) | idct_sse2_row_perm[i & 7]] = src[i];
        return 1;
    }

    return 0;
}