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
typedef  int /*<<< orphan*/  vec_f ;

/* Variables and functions */
 int /*<<< orphan*/  vec_madd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_vsx_ld (int /*<<< orphan*/ ,float const*) ; 
 int /*<<< orphan*/  vec_vsx_st (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 

void ff_vector_fmul_add_vsx(float *dst, const float *src0,
                            const float *src1, const float *src2,
                            int len)
{
    int i;
    vec_f d, s0, s1, s2;

    for (i = 0; i < len - 3; i += 4) {
        s0 = vec_vsx_ld(0, src0 + i);
        s1 = vec_vsx_ld(0, src1 + i);
        s2 = vec_vsx_ld(0, src2 + i);
        d = vec_madd(s0, s1, s2);
        vec_vsx_st(d, 0, dst + i);
    }
}