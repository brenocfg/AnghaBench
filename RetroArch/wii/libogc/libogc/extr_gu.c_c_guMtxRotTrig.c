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
typedef  float f32 ;
typedef  float** Mtx ;

/* Variables and functions */

void c_guMtxRotTrig(Mtx mt,const char axis,f32 sinA,f32 cosA)
{
	switch(axis) {
		case 'x':
		case 'X':
			mt[0][0] =  1.0f;  mt[0][1] =  0.0f;    mt[0][2] =  0.0f;  mt[0][3] = 0.0f;
			mt[1][0] =  0.0f;  mt[1][1] =  cosA;    mt[1][2] = -sinA;  mt[1][3] = 0.0f;
			mt[2][0] =  0.0f;  mt[2][1] =  sinA;    mt[2][2] =  cosA;  mt[2][3] = 0.0f;
			break;
		case 'y':
		case 'Y':
			mt[0][0] =  cosA;  mt[0][1] =  0.0f;    mt[0][2] =  sinA;  mt[0][3] = 0.0f;
			mt[1][0] =  0.0f;  mt[1][1] =  1.0f;    mt[1][2] =  0.0f;  mt[1][3] = 0.0f;
			mt[2][0] = -sinA;  mt[2][1] =  0.0f;    mt[2][2] =  cosA;  mt[2][3] = 0.0f;
			break;
		case 'z':
		case 'Z':
			mt[0][0] =  cosA;  mt[0][1] = -sinA;    mt[0][2] =  0.0f;  mt[0][3] = 0.0f;
			mt[1][0] =  sinA;  mt[1][1] =  cosA;    mt[1][2] =  0.0f;  mt[1][3] = 0.0f;
			mt[2][0] =  0.0f;  mt[2][1] =  0.0f;    mt[2][2] =  1.0f;  mt[2][3] = 0.0f;
			break;
		default:
			break;
	}
}