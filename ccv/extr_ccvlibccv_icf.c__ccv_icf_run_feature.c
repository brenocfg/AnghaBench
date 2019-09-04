#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float beta; int count; int* channel; float* alpha; TYPE_1__* sat; } ;
typedef  TYPE_2__ ccv_icf_feature_t ;
struct TYPE_4__ {int x; int y; } ;

/* Variables and functions */

__attribute__((used)) static inline float _ccv_icf_run_feature(ccv_icf_feature_t* feature, float* ptr, int cols, int ch, int x, int y)
{
	float c = feature->beta;
	int q;
	for (q = 0; q < feature->count; q++)
		c += (ptr[(feature->sat[q * 2 + 1].x + x + 1 + (feature->sat[q * 2 + 1].y + y + 1) * cols) * ch + feature->channel[q]] - ptr[(feature->sat[q * 2].x + x + (feature->sat[q * 2 + 1].y + y + 1) * cols) * ch + feature->channel[q]] + ptr[(feature->sat[q * 2].x + x + (feature->sat[q * 2].y + y) * cols) * ch + feature->channel[q]] - ptr[(feature->sat[q * 2 + 1].x + x + 1 + (feature->sat[q * 2].y + y) * cols) * ch + feature->channel[q]]) * feature->alpha[q];
	return c;
}