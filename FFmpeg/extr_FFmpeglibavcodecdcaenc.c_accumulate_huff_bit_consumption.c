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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SUBBAND_SAMPLES ; 
 size_t* ff_dca_quant_index_group_size ; 
 scalar_t__ ff_dca_vlc_calc_quant_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static void accumulate_huff_bit_consumption(int abits, int32_t *quantized,
                                            uint32_t *result)
{
    uint8_t sel, id = abits - 1;
    for (sel = 0; sel < ff_dca_quant_index_group_size[id]; sel++)
        result[sel] += ff_dca_vlc_calc_quant_bits(quantized, SUBBAND_SAMPLES,
                                                  sel, id);
}