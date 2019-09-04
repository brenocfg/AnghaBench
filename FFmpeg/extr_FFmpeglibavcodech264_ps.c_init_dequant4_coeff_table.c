#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int*** dequant4_coeff; int*** dequant4_buffer; int** scaling_matrix4; } ;
struct TYPE_5__ {int bit_depth_luma; } ;
typedef  TYPE_1__ SPS ;
typedef  TYPE_2__ PPS ;

/* Variables and functions */
 scalar_t__** ff_h264_dequant4_coeff_init ; 
 int* ff_h264_quant_div6 ; 
 int* ff_h264_quant_rem6 ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 

__attribute__((used)) static void init_dequant4_coeff_table(PPS *pps, const SPS *sps)
{
    int i, j, q, x;
    const int max_qp = 51 + 6 * (sps->bit_depth_luma - 8);
    for (i = 0; i < 6; i++) {
        pps->dequant4_coeff[i] = pps->dequant4_buffer[i];
        for (j = 0; j < i; j++)
            if (!memcmp(pps->scaling_matrix4[j], pps->scaling_matrix4[i],
                        16 * sizeof(uint8_t))) {
                pps->dequant4_coeff[i] = pps->dequant4_buffer[j];
                break;
            }
        if (j < i)
            continue;

        for (q = 0; q < max_qp + 1; q++) {
            int shift = ff_h264_quant_div6[q] + 2;
            int idx   = ff_h264_quant_rem6[q];
            for (x = 0; x < 16; x++)
                pps->dequant4_coeff[i][q][(x >> 2) | ((x << 2) & 0xF)] =
                    ((uint32_t)ff_h264_dequant4_coeff_init[idx][(x & 1) + ((x >> 2) & 1)] *
                     pps->scaling_matrix4[i][x]) << shift;
        }
    }
}