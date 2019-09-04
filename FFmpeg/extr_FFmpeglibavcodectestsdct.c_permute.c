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
#define  FF_IDCT_PERM_LIBMPEG2 130 
#define  FF_IDCT_PERM_PARTTRANS 129 
#define  FF_IDCT_PERM_TRANSPOSE 128 

__attribute__((used)) static void permute(int16_t dst[64], const int16_t src[64],
                    enum idct_permutation_type perm_type)
{
    int i;

#if ARCH_X86
    if (permute_x86(dst, src, perm_type))
        return;
#endif

    switch (perm_type) {
    case FF_IDCT_PERM_LIBMPEG2:
        for (i = 0; i < 64; i++)
            dst[(i & 0x38) | ((i & 6) >> 1) | ((i & 1) << 2)] = src[i];
        break;
    case FF_IDCT_PERM_PARTTRANS:
        for (i = 0; i < 64; i++)
            dst[(i & 0x24) | ((i & 3) << 3) | ((i >> 3) & 3)] = src[i];
        break;
    case FF_IDCT_PERM_TRANSPOSE:
        for (i = 0; i < 64; i++)
            dst[(i>>3) | ((i<<3)&0x38)] = src[i];
        break;
    default:
        for (i = 0; i < 64; i++)
            dst[i] = src[i];
        break;
    }
}