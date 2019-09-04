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
typedef  int /*<<< orphan*/  vec_u8 ;
typedef  scalar_t__ vec_f ;

/* Variables and functions */
 int /*<<< orphan*/  vcprm (int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vec_ld (int,float const*) ; 
 scalar_t__ vec_madd (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ vec_nmsub (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ vec_perm (scalar_t__,scalar_t__,int /*<<< orphan*/  const) ; 
 scalar_t__ vec_splat_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_st (scalar_t__,int,float*) ; 

void ff_vector_fmul_window_altivec(float *dst, const float *src0,
                                   const float *src1, const float *win, int len)
{
    vec_f zero, t0, t1, s0, s1, wi, wj;
    const vec_u8 reverse = vcprm(3, 2, 1, 0);
    int i, j;

    dst  += len;
    win  += len;
    src0 += len;

    zero = (vec_f)vec_splat_u32(0);

    for (i = -len * 4, j = len * 4 - 16; i < 0; i += 16, j -= 16) {
        s0 = vec_ld(i, src0);
        s1 = vec_ld(j, src1);
        wi = vec_ld(i, win);
        wj = vec_ld(j, win);

        s1 = vec_perm(s1, s1, reverse);
        wj = vec_perm(wj, wj, reverse);

        t0 = vec_madd(s0, wj, zero);
        t0 = vec_nmsub(s1, wi, t0);
        t1 = vec_madd(s0, wi, zero);
        t1 = vec_madd(s1, wj, t1);
        t1 = vec_perm(t1, t1, reverse);

        vec_st(t0, i, dst);
        vec_st(t1, j, dst);
    }
}