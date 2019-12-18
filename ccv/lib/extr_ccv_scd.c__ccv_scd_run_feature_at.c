#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* sy; int* sx; int* dy; int* dx; } ;
typedef  TYPE_1__ ccv_scd_stump_feature_t ;

/* Variables and functions */
 int CCV_SCD_CHANNEL ; 
 float ccv_clamp (float,float,float) ; 
 int sqrtf (float) ; 

__attribute__((used)) static inline void _ccv_scd_run_feature_at(float* at, int cols, ccv_scd_stump_feature_t* feature, float surf[32])
{
	int i, j;
	// extract feature
	for (i = 0; i < 4; i++)
	{
		float* d = at + (cols * feature->sy[i] + feature->sx[i]) * CCV_SCD_CHANNEL;
		float* du = at + (cols * feature->dy[i] + feature->sx[i]) * CCV_SCD_CHANNEL;
		float* dv = at + (cols * feature->sy[i] + feature->dx[i]) * CCV_SCD_CHANNEL;
		float* duv = at + (cols * feature->dy[i] + feature->dx[i]) * CCV_SCD_CHANNEL;
		for (j = 0; j < 8; j++)
			surf[i * 8 + j] = duv[j] - du[j] + d[j] - dv[j];
	}
	// L2Hys normalization
	float v = 0;
	for (i = 0; i < 32; i++)
		v += surf[i] * surf[i];
	v = 1.0 / (sqrtf(v) + 1e-6);
	static float theta = 2.0 / 5.65685424949; // sqrtf(32)
	float u = 0;
	for (i = 0; i < 32; i++)
	{
		surf[i] = surf[i] * v;
		surf[i] = ccv_clamp(surf[i], -theta, theta);
		u += surf[i] * surf[i];
	}
	u = 1.0 / (sqrtf(u) + 1e-6);
	for (i = 0; i < 32; i++)
		surf[i] = surf[i] * u;
}