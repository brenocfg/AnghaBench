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
typedef  int uint8_t ;

/* Variables and functions */
 int* ff_celt_hadamard_order ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 

__attribute__((used)) static void celt_interleave_hadamard(float *tmp, float *X, int N0,
                                     int stride, int hadamard)
{
    int i, j, N = N0*stride;
    const uint8_t *order = &ff_celt_hadamard_order[hadamard ? stride - 2 : 30];

    for (i = 0; i < stride; i++)
        for (j = 0; j < N0; j++)
            tmp[j*stride+i] = X[order[i]*N0+j];

    memcpy(X, tmp, N*sizeof(float));
}