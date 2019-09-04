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

/* Variables and functions */
 float FLT_EPSILON ; 
 float ccv_max (float const,float) ; 
 float fast_cube_root (float const) ; 

__attribute__((used)) static inline void _ccv_rgb_to_luv(const float r, const float g, const float b, float* pl, float* pu, float* pv)
{
	const float x = 0.412453f * r + 0.35758f * g + 0.180423f * b;
	const float y = 0.212671f * r + 0.71516f * g + 0.072169f * b;
	const float z = 0.019334f * r + 0.119193f * g + 0.950227f * b;

	const float x_n = 0.312713f, y_n = 0.329016f;
	const float uv_n_divisor = -2.f * x_n + 12.f * y_n + 3.f;
	const float u_n = 4.f * x_n / uv_n_divisor;
	const float v_n = 9.f * y_n / uv_n_divisor;

    const float uv_divisor = ccv_max((x + 15.f * y + 3.f * z), FLT_EPSILON);
	const float u = 4.f * x / uv_divisor;
	const float v = 9.f * y / uv_divisor;

	const float y_cube_root = fast_cube_root(y);

	const float l_value = ccv_max(0.f, ((116.f * y_cube_root) - 16.f));
	const float u_value = 13.f * l_value * (u - u_n);
	const float v_value = 13.f * l_value * (v - v_n);

	// L in [0, 100], U in [-134, 220], V in [-140, 122]
	*pl = l_value * (255.f / 100.f);
	*pu = (u_value + 134.f) * (255.f / (220.f + 134.f));
	*pv = (v_value + 140.f) * (255.f / (122.f + 140.f));
}