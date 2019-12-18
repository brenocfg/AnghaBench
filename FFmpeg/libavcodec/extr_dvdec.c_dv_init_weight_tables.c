#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int height; } ;
struct TYPE_6__ {int* idct_factor; } ;
typedef  TYPE_1__ DVVideoContext ;
typedef  TYPE_2__ AVDVProfile ;

/* Variables and functions */
 scalar_t__ DV_PROFILE_IS_HD (TYPE_2__ const*) ; 
 int* dv_iweight_1080_c ; 
 int* dv_iweight_1080_y ; 
 int* dv_iweight_248 ; 
 int* dv_iweight_720_c ; 
 int* dv_iweight_720_y ; 
 int* dv_iweight_88 ; 
 int** ff_dv_quant_shifts ; 

__attribute__((used)) static void dv_init_weight_tables(DVVideoContext *ctx, const AVDVProfile *d)
{
    int j, i, c, s;
    uint32_t *factor1 = &ctx->idct_factor[0],
             *factor2 = &ctx->idct_factor[DV_PROFILE_IS_HD(d) ? 4096 : 2816];

    if (DV_PROFILE_IS_HD(d)) {
        /* quantization quanta by QNO for DV100 */
        static const uint8_t dv100_qstep[16] = {
            1, /* QNO = 0 and 1 both have no quantization */
            1,
            2, 3, 4, 5, 6, 7, 8, 16, 18, 20, 22, 24, 28, 52
        };
        const uint16_t *iweight1, *iweight2;

        if (d->height == 720) {
            iweight1 = &dv_iweight_720_y[0];
            iweight2 = &dv_iweight_720_c[0];
        } else {
            iweight1 = &dv_iweight_1080_y[0];
            iweight2 = &dv_iweight_1080_c[0];
        }
        for (c = 0; c < 4; c++) {
            for (s = 0; s < 16; s++) {
                for (i = 0; i < 64; i++) {
                    *factor1++ = (dv100_qstep[s] << (c + 9)) * iweight1[i];
                    *factor2++ = (dv100_qstep[s] << (c + 9)) * iweight2[i];
                }
            }
        }
    } else {
        static const uint8_t dv_quant_areas[4] = { 6, 21, 43, 64 };
        const uint16_t *iweight1 = &dv_iweight_88[0];
        for (j = 0; j < 2; j++, iweight1 = &dv_iweight_248[0]) {
            for (s = 0; s < 22; s++) {
                for (i = c = 0; c < 4; c++) {
                    for (; i < dv_quant_areas[c]; i++) {
                        *factor1   = iweight1[i] << (ff_dv_quant_shifts[s][c] + 1);
                        *factor2++ = (*factor1++) << 1;
                    }
                }
            }
        }
    }
}