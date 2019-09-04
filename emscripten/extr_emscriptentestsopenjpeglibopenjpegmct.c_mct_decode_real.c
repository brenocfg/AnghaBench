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
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_add_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_load_ps (float*) ; 
 int /*<<< orphan*/  _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set1_ps (float) ; 
 int /*<<< orphan*/  _mm_store_ps (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_sub_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mct_decode_real(
		float* restrict c0,
		float* restrict c1,
		float* restrict c2,
		int n)
{
	int i;
#ifdef __SSE__
	__m128 vrv, vgu, vgv, vbu;
	vrv = _mm_set1_ps(1.402f);
	vgu = _mm_set1_ps(0.34413f);
	vgv = _mm_set1_ps(0.71414f);
	vbu = _mm_set1_ps(1.772f);
	for (i = 0; i < (n >> 3); ++i) {
		__m128 vy, vu, vv;
		__m128 vr, vg, vb;

		vy = _mm_load_ps(c0);
		vu = _mm_load_ps(c1);
		vv = _mm_load_ps(c2);
		vr = _mm_add_ps(vy, _mm_mul_ps(vv, vrv));
		vg = _mm_sub_ps(_mm_sub_ps(vy, _mm_mul_ps(vu, vgu)), _mm_mul_ps(vv, vgv));
		vb = _mm_add_ps(vy, _mm_mul_ps(vu, vbu));
		_mm_store_ps(c0, vr);
		_mm_store_ps(c1, vg);
		_mm_store_ps(c2, vb);
		c0 += 4;
		c1 += 4;
		c2 += 4;

		vy = _mm_load_ps(c0);
		vu = _mm_load_ps(c1);
		vv = _mm_load_ps(c2);
		vr = _mm_add_ps(vy, _mm_mul_ps(vv, vrv));
		vg = _mm_sub_ps(_mm_sub_ps(vy, _mm_mul_ps(vu, vgu)), _mm_mul_ps(vv, vgv));
		vb = _mm_add_ps(vy, _mm_mul_ps(vu, vbu));
		_mm_store_ps(c0, vr);
		_mm_store_ps(c1, vg);
		_mm_store_ps(c2, vb);
		c0 += 4;
		c1 += 4;
		c2 += 4;
	}
	n &= 7;
#endif
	for(i = 0; i < n; ++i) {
		float y = c0[i];
		float u = c1[i];
		float v = c2[i];
		float r = y + (v * 1.402f);
		float g = y - (u * 0.34413f) - (v * (0.71414f));
		float b = y + (u * 1.772f);
		c0[i] = r;
		c1[i] = g;
		c2[i] = b;
	}
}