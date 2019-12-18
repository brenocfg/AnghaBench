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
typedef  int f32 ;
typedef  int** Mtx ;

/* Variables and functions */

void c_guMtxApplyScale(Mtx src,Mtx dst,f32 xS,f32 yS,f32 zS)
{
	dst[0][0] = src[0][0] * xS;     dst[0][1] = src[0][1] * yS;
	dst[0][2] = src[0][2] * zS;     dst[0][3] = src[0][3];

	dst[1][0] = src[1][0] * xS;     dst[1][1] = src[1][1] * yS;
	dst[1][2] = src[1][2] * zS;     dst[1][3] = src[1][3];

	dst[2][0] = src[2][0] * xS;     dst[2][1] = src[2][1] * yS;
	dst[2][2] = src[2][2] * zS;     dst[2][3] = src[2][3];
}