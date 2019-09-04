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
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static void dss_sp_scale_vector(int32_t *vec, int bits, int size)
{
    int i;

    if (bits < 0)
        for (i = 0; i < size; i++)
            vec[i] = vec[i] >> -bits;
    else
        for (i = 0; i < size; i++)
            vec[i] = vec[i] * (1 << bits);
}