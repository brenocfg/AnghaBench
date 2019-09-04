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
 int /*<<< orphan*/  s0 ; 
 int s1 ; 
 int s2 ; 
 int s3 ; 
 int /*<<< orphan*/  vcprm (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  vec_ld (int,float const*) ; 
 int /*<<< orphan*/  vec_madd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_st (int /*<<< orphan*/ ,int,float*) ; 

void ff_vector_fmul_add_altivec(float *dst, const float *src0,
                                const float *src1, const float *src2,
                                int len)
{
    int i;
    vec_f d, ss0, ss1, ss2, t0, t1, edges;

    for (i = 0; i < len - 3; i += 4) {
        t0 = vec_ld(0, dst + i);
        t1 = vec_ld(15, dst + i);
        ss0 = vec_ld(0, src0 + i);
        ss1 = vec_ld(0, src1 + i);
        ss2 = vec_ld(0, src2 + i);
        edges = vec_perm(t1, t0, vcprm(0, 1, 2, 3));
        d = vec_madd(ss0, ss1, ss2);
        t1 = vec_perm(d, edges, vcprm(s0,s1,s2,s3));
        t0 = vec_perm(edges, d, vcprm(s0,s1,s2,s3));
        vec_st(t1, 15, dst + i);
        vec_st(t0, 0, dst + i);
    }
}