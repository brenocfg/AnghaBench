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
 int /*<<< orphan*/  memcpy (float*,float const* const,int) ; 

__attribute__((used)) static void dequant(float *out, const int *idx, const float * const cbs[])
{
    int i;

    for (i = 0; i < 4; i++)
        memcpy(out + 3*i, cbs[i] + 3*idx[i], 3*sizeof(float));

    memcpy(out + 12, cbs[4] + 4*idx[4], 4*sizeof(float));
}