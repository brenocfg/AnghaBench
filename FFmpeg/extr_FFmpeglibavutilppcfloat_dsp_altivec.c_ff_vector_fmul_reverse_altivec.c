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
 int /*<<< orphan*/  vec_ld (int,float const*) ; 
 int /*<<< orphan*/  vec_madd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_mergeh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_mergel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_splat_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_st (int /*<<< orphan*/ ,int,float*) ; 

void ff_vector_fmul_reverse_altivec(float *dst, const float *src0,
                                    const float *src1, int len)
{
    int i;
    vec_f d, s0, s1, h0, l0, s2, s3;
    vec_f zero = (vec_f)vec_splat_u32(0);

    src1 += len-4;
    for(i = 0; i < len - 7; i += 8) {
        s1 = vec_ld(0, src1 - i);              // [a,b,c,d]
        s0 = vec_ld(0, src0 + i);
        l0 = vec_mergel(s1, s1);               // [c,c,d,d]
        s3 = vec_ld(-16, src1 - i);
        h0 = vec_mergeh(s1, s1);               // [a,a,b,b]
        s2 = vec_ld(16, src0 + i);
        s1 = vec_mergeh(vec_mergel(l0, h0),    // [d,b,d,b]
                        vec_mergeh(l0, h0));   // [c,a,c,a]
        // [d,c,b,a]
        l0 = vec_mergel(s3, s3);
        d = vec_madd(s0, s1, zero);
        h0 = vec_mergeh(s3, s3);
        vec_st(d, 0, dst + i);
        s3 = vec_mergeh(vec_mergel(l0, h0),
                        vec_mergeh(l0, h0));
        d = vec_madd(s2, s3, zero);
        vec_st(d, 16, dst + i);
    }
}