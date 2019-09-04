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
typedef  int /*<<< orphan*/  v4 ;
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_add_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4dwt_decode_step2_sse(v4* l, v4* w, int k, int m, __m128 c){
	__m128* restrict vl = (__m128*) l;
	__m128* restrict vw = (__m128*) w;
	int i;
	__m128 tmp1, tmp2, tmp3;
	tmp1 = vl[0];
	for(i = 0; i < m; ++i){
		tmp2 = vw[-1];
		tmp3 = vw[ 0];
		vw[-1] = _mm_add_ps(tmp2, _mm_mul_ps(_mm_add_ps(tmp1, tmp3), c));
		tmp1 = tmp3;
		vw += 2;
	}
	vl = vw - 2;
	if(m >= k){
		return;
	}
	c = _mm_add_ps(c, c);
	c = _mm_mul_ps(c, vl[0]);
	for(; m < k; ++m){
		__m128 tmp = vw[-1];
		vw[-1] = _mm_add_ps(tmp, c);
		vw += 2;
	}
}