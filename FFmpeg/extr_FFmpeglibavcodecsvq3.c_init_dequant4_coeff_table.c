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
typedef  int uint32_t ;
struct TYPE_3__ {int** dequant4_coeff; } ;
typedef  TYPE_1__ SVQ3Context ;

/* Variables and functions */
 scalar_t__** ff_h264_dequant4_coeff_init ; 
 int* ff_h264_quant_div6 ; 
 int* ff_h264_quant_rem6 ; 

__attribute__((used)) static void init_dequant4_coeff_table(SVQ3Context *s)
{
    int q, x;
    const int max_qp = 51;

    for (q = 0; q < max_qp + 1; q++) {
        int shift = ff_h264_quant_div6[q] + 2;
        int idx   = ff_h264_quant_rem6[q];
        for (x = 0; x < 16; x++)
            s->dequant4_coeff[q][(x >> 2) | ((x << 2) & 0xF)] =
                ((uint32_t)ff_h264_dequant4_coeff_init[idx][(x & 1) + ((x >> 2) & 1)] * 16) << shift;
    }
}