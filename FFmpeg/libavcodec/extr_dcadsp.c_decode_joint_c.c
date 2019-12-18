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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  clip23 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul17 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_joint_c(int32_t **dst, int32_t **src,
                           const int32_t *scale_factors,
                           ptrdiff_t sb_start, ptrdiff_t sb_end,
                           ptrdiff_t ofs, ptrdiff_t len)
{
    int i, j;

    for (i = sb_start; i < sb_end; i++) {
        int32_t scale = scale_factors[i];
        for (j = 0; j < len; j++)
            dst[i][j + ofs] = clip23(mul17(src[i][j + ofs], scale));
    }
}