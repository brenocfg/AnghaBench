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
struct TYPE_3__ {int /*<<< orphan*/  random_state; } ;
typedef  TYPE_1__ COOKContext ;

/* Variables and functions */
 int SUBBAND_SIZE ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 float* dither_tab ; 
 float** quant_centroid_tab ; 
 float* rootpow2tab ; 

__attribute__((used)) static void scalar_dequant_float(COOKContext *q, int index, int quant_index,
                                 int *subband_coef_index, int *subband_coef_sign,
                                 float *mlt_p)
{
    int i;
    float f1;

    for (i = 0; i < SUBBAND_SIZE; i++) {
        if (subband_coef_index[i]) {
            f1 = quant_centroid_tab[index][subband_coef_index[i]];
            if (subband_coef_sign[i])
                f1 = -f1;
        } else {
            /* noise coding if subband_coef_index[i] == 0 */
            f1 = dither_tab[index];
            if (av_lfg_get(&q->random_state) < 0x80000000)
                f1 = -f1;
        }
        mlt_p[i] = f1 * rootpow2tab[quant_index + 63];
    }
}