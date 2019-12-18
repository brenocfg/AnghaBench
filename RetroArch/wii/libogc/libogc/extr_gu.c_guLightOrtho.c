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

void guLightOrtho(Mtx mt,f32 t,f32 b,f32 l,f32 r,f32 scaleS,f32 scaleT,f32 transS,f32 transT)
{
	f32 tmp;

    tmp     =  1.0f / (r - l);
    mt[0][0] =  (2.0f * tmp * scaleS);
    mt[0][1] =  0.0f;
    mt[0][2] =  0.0f;
    mt[0][3] =  ((-(r + l) * tmp) * scaleS) + transS;

    tmp     =  1.0f / (t - b);
    mt[1][0] =  0.0f;
    mt[1][1] =  (2.0f * tmp) * scaleT;
    mt[1][2] =  0.0f;
    mt[1][3] =  ((-(t + b) * tmp)* scaleT) + transT;

    mt[2][0] =  0.0f;
    mt[2][1] =  0.0f;
    mt[2][2] =  0.0f;
    mt[2][3] =  1.0f;
}