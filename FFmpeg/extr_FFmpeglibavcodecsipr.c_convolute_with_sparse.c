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
struct TYPE_3__ {int n; int* x; float const* y; } ;
typedef  TYPE_1__ AMRFixed ;

/* Variables and functions */
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void convolute_with_sparse(float *out, const AMRFixed *pulses,
                                  const float *shape, int length)
{
    int i, j;

    memset(out, 0, length*sizeof(float));
    for (i = 0; i < pulses->n; i++)
        for (j = pulses->x[i]; j < length; j++)
            out[j] += pulses->y[i] * shape[j - pulses->x[i]];
}