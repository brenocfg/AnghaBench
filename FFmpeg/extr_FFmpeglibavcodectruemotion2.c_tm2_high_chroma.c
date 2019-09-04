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

__attribute__((used)) static inline void tm2_high_chroma(int *data, int stride, int *last, unsigned *CD, int *deltas)
{
    int i, j;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 2; i++)  {
            CD[j]   += deltas[i + j * 2];
            last[i] += CD[j];
            data[i]  = last[i];
        }
        data += stride;
    }
}