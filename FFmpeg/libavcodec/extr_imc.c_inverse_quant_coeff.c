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
struct TYPE_3__ {float* CWdecoded; int* CWlengthT; int* codewords; float const* flcoeffs6; int* bandFlagsBuf; scalar_t__* skipFlags; } ;
typedef  int /*<<< orphan*/  IMCContext ;
typedef  TYPE_1__ IMCChannel ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int BANDS ; 
 int* band_tab ; 
 float** imc_quantizer1 ; 
 float** imc_quantizer2 ; 

__attribute__((used)) static int inverse_quant_coeff(IMCContext *q, IMCChannel *chctx,
                               int stream_format_code)
{
    int i, j;
    int middle_value, cw_len, max_size;
    const float *quantizer;

    for (i = 0; i < BANDS; i++) {
        for (j = band_tab[i]; j < band_tab[i + 1]; j++) {
            chctx->CWdecoded[j] = 0;
            cw_len = chctx->CWlengthT[j];

            if (cw_len <= 0 || chctx->skipFlags[j])
                continue;

            max_size     = 1 << cw_len;
            middle_value = max_size >> 1;

            if (chctx->codewords[j] >= max_size || chctx->codewords[j] < 0)
                return AVERROR_INVALIDDATA;

            if (cw_len >= 4) {
                quantizer = imc_quantizer2[(stream_format_code & 2) >> 1];
                if (chctx->codewords[j] >= middle_value)
                    chctx->CWdecoded[j] =  quantizer[chctx->codewords[j] - 8]                * chctx->flcoeffs6[i];
                else
                    chctx->CWdecoded[j] = -quantizer[max_size - chctx->codewords[j] - 8 - 1] * chctx->flcoeffs6[i];
            }else{
                quantizer = imc_quantizer1[((stream_format_code & 2) >> 1) | (chctx->bandFlagsBuf[i] << 1)];
                if (chctx->codewords[j] >= middle_value)
                    chctx->CWdecoded[j] =  quantizer[chctx->codewords[j] - 1]            * chctx->flcoeffs6[i];
                else
                    chctx->CWdecoded[j] = -quantizer[max_size - 2 - chctx->codewords[j]] * chctx->flcoeffs6[i];
            }
        }
    }
    return 0;
}