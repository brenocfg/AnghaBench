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
 size_t* ff_zigzag_direct ; 
 int* unscaled_quant_matrix ; 

__attribute__((used)) static void compute_quant_matrix(int *output, int qscale)
{
    int i;
    for (i = 0; i < 64; i++) output[i] = unscaled_quant_matrix[ff_zigzag_direct[i]] * qscale;
}