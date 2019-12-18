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

void c_guMtxTrans(Mtx mt,f32 xT,f32 yT,f32 zT)
{
    mt[0][0] = 1.0f;  mt[0][1] = 0.0f;  mt[0][2] = 0.0f;  mt[0][3] =  xT;
    mt[1][0] = 0.0f;  mt[1][1] = 1.0f;  mt[1][2] = 0.0f;  mt[1][3] =  yT;
    mt[2][0] = 0.0f;  mt[2][1] = 0.0f;  mt[2][2] = 1.0f;  mt[2][3] =  zT;
}