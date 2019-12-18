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

void matrix_init_orthographic(float *m, float left, float right, float bottom, float top, float near, float far)
{
	m[0x0] = 2.0f/(right-left);
	m[0x4] = 0.0f;
	m[0x8] = 0.0f;
	m[0xC] = -(right+left)/(right-left);

	m[0x1] = 0.0f;
	m[0x5] = 2.0f/(top-bottom);
	m[0x9] = 0.0f;
	m[0xD] = -(top+bottom)/(top-bottom);

	m[0x2] = 0.0f;
	m[0x6] = 0.0f;
	m[0xA] = -2.0f/(far-near);
	m[0xE] = (far+near)/(far-near);

	m[0x3] = 0.0f;
	m[0x7] = 0.0f;
	m[0xB] = 0.0f;
	m[0xF] = 1.0f;
}