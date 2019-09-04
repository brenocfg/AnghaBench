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
 float* isfp_inter ; 

__attribute__((used)) static void interpolate_isp(double isp_q[4][LP_ORDER], const double *isp4_past)
{
    int i, k;

    for (k = 0; k < 3; k++) {
        float c = isfp_inter[k];
        for (i = 0; i < LP_ORDER; i++)
            isp_q[k][i] = (1.0 - c) * isp4_past[i] + c * isp_q[3][i];
    }
}