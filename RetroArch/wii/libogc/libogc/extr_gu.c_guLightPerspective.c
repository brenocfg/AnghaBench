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
 float DegToRad (float) ; 
 float tanf (float) ; 

void guLightPerspective(Mtx mt,f32 fovY,f32 aspect,f32 scaleS,f32 scaleT,f32 transS,f32 transT)
{
	f32 angle;
	f32 cot;

	angle = fovY*0.5f;
	angle = DegToRad(angle);

	cot = 1.0f/tanf(angle);

    mt[0][0] =    (cot / aspect) * scaleS;
    mt[0][1] =    0.0f;
    mt[0][2] =    -transS;
    mt[0][3] =    0.0f;

    mt[1][0] =    0.0f;
    mt[1][1] =    cot * scaleT;
    mt[1][2] =    -transT;
    mt[1][3] =    0.0f;

    mt[2][0] =    0.0f;
    mt[2][1] =    0.0f;
    mt[2][2] =   -1.0f;
    mt[2][3] =    0.0f;
}