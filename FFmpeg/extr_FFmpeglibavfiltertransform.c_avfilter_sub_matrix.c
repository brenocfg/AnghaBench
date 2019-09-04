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

void avfilter_sub_matrix(const float *m1, const float *m2, float *result)
{
    int i;
    for (i = 0; i < 9; i++)
        result[i] = m1[i] - m2[i];
}