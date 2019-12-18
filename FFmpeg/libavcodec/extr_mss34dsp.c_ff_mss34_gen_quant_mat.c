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
typedef  int uint16_t ;

/* Variables and functions */
 int* chroma_quant ; 
 int* luma_quant ; 

void ff_mss34_gen_quant_mat(uint16_t *qmat, int quality, int luma)
{
    int i;
    const uint8_t *qsrc = luma ? luma_quant : chroma_quant;

    if (quality >= 50) {
        int scale = 200 - 2 * quality;

        for (i = 0; i < 64; i++)
            qmat[i] = (qsrc[i] * scale + 50) / 100;
    } else {
        for (i = 0; i < 64; i++)
            qmat[i] = (5000 * qsrc[i] / quality + 50) / 100;
    }
}