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
 int LP_ORDER ; 
 float PRED_FACTOR ; 
 float* isf_mean ; 

__attribute__((used)) static void isf_add_mean_and_past(float *isf_q, float *isf_past)
{
    int i;
    float tmp;

    for (i = 0; i < LP_ORDER; i++) {
        tmp = isf_q[i];
        isf_q[i] += isf_mean[i] * (1.0f / (1 << 15));
        isf_q[i] += PRED_FACTOR * isf_past[i];
        isf_past[i] = tmp;
    }
}