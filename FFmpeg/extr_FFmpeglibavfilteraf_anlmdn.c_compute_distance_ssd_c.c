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
typedef  int ptrdiff_t ;

/* Variables and functions */
 scalar_t__ SQR (float const) ; 

__attribute__((used)) static float compute_distance_ssd_c(const float *f1, const float *f2, ptrdiff_t K)
{
    float distance = 0.;

    for (int k = -K; k <= K; k++)
        distance += SQR(f1[k] - f2[k]);

    return distance;
}