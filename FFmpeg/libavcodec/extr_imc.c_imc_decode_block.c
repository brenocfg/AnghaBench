#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ codec_id; int /*<<< orphan*/  channels; } ;
struct TYPE_25__ {int decoder_reset; double* old_floor; int* levlCoeffBuf; scalar_t__* flcoeffs1; int* flcoeffs2; int* bandWidthT; int* flcoeffs3; double* flcoeffs5; int* bitsBandT; int* CWlengthT; void** skipFlags; void** codewords; scalar_t__* sumLenArr; void** bandFlagsBuf; scalar_t__* CWdecoded; } ;
struct TYPE_24__ {int /*<<< orphan*/  gb; TYPE_2__* chctx; } ;
typedef  TYPE_1__ IMCContext ;
typedef  TYPE_2__ IMCChannel ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_IAC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int BANDS ; 
 int COEFFS ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int* band_tab ; 
 int bit_allocation (TYPE_1__*,TYPE_2__*,int,scalar_t__,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imc_calculate_coeffs (TYPE_1__*,scalar_t__*,int*,int*,int*,double*) ; 
 int /*<<< orphan*/  imc_decode_level_coefficients (TYPE_1__*,int*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  imc_decode_level_coefficients2 (TYPE_1__*,int*,double*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  imc_decode_level_coefficients_raw (TYPE_1__*,int*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  imc_get_coeffs (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  imc_imdct256 (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imc_read_level_coeffs (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  imc_read_level_coeffs_raw (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  imc_refine_bit_allocation (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ inverse_quant_coeff (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (double*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int imc_decode_block(AVCodecContext *avctx, IMCContext *q, int ch)
{
    int stream_format_code;
    int imc_hdr, i, j, ret;
    int flag;
    int bits;
    int counter, bitscount;
    IMCChannel *chctx = q->chctx + ch;


    /* Check the frame header */
    imc_hdr = get_bits(&q->gb, 9);
    if (imc_hdr & 0x18) {
        av_log(avctx, AV_LOG_ERROR, "frame header check failed!\n");
        av_log(avctx, AV_LOG_ERROR, "got %X.\n", imc_hdr);
        return AVERROR_INVALIDDATA;
    }
    stream_format_code = get_bits(&q->gb, 3);

    if (stream_format_code & 0x04)
        chctx->decoder_reset = 1;

    if (chctx->decoder_reset) {
        for (i = 0; i < BANDS; i++)
            chctx->old_floor[i] = 1.0;
        for (i = 0; i < COEFFS; i++)
            chctx->CWdecoded[i] = 0;
        chctx->decoder_reset = 0;
    }

    flag = get_bits1(&q->gb);
    if (stream_format_code & 0x1)
        imc_read_level_coeffs_raw(q, stream_format_code, chctx->levlCoeffBuf);
    else
        imc_read_level_coeffs(q, stream_format_code, chctx->levlCoeffBuf);

    if (stream_format_code & 0x1)
        imc_decode_level_coefficients_raw(q, chctx->levlCoeffBuf,
                                          chctx->flcoeffs1, chctx->flcoeffs2);
    else if (stream_format_code & 0x4)
        imc_decode_level_coefficients(q, chctx->levlCoeffBuf,
                                      chctx->flcoeffs1, chctx->flcoeffs2);
    else
        imc_decode_level_coefficients2(q, chctx->levlCoeffBuf, chctx->old_floor,
                                       chctx->flcoeffs1, chctx->flcoeffs2);

    for(i=0; i<BANDS; i++) {
        if(chctx->flcoeffs1[i] > INT_MAX) {
            av_log(avctx, AV_LOG_ERROR, "scalefactor out of range\n");
            return AVERROR_INVALIDDATA;
        }
    }

    memcpy(chctx->old_floor, chctx->flcoeffs1, 32 * sizeof(float));

    counter = 0;
    if (stream_format_code & 0x1) {
        for (i = 0; i < BANDS; i++) {
            chctx->bandWidthT[i]   = band_tab[i + 1] - band_tab[i];
            chctx->bandFlagsBuf[i] = 0;
            chctx->flcoeffs3[i]    = chctx->flcoeffs2[i] * 2;
            chctx->flcoeffs5[i]    = 1.0;
        }
    } else {
        for (i = 0; i < BANDS; i++) {
            if (chctx->levlCoeffBuf[i] == 16) {
                chctx->bandWidthT[i] = 0;
                counter++;
            } else
                chctx->bandWidthT[i] = band_tab[i + 1] - band_tab[i];
        }

        memset(chctx->bandFlagsBuf, 0, BANDS * sizeof(int));
        for (i = 0; i < BANDS - 1; i++)
            if (chctx->bandWidthT[i])
                chctx->bandFlagsBuf[i] = get_bits1(&q->gb);

        imc_calculate_coeffs(q, chctx->flcoeffs1, chctx->flcoeffs2,
                             chctx->bandWidthT, chctx->flcoeffs3,
                             chctx->flcoeffs5);
    }

    bitscount = 0;
    /* first 4 bands will be assigned 5 bits per coefficient */
    if (stream_format_code & 0x2) {
        bitscount += 15;

        chctx->bitsBandT[0] = 5;
        chctx->CWlengthT[0] = 5;
        chctx->CWlengthT[1] = 5;
        chctx->CWlengthT[2] = 5;
        for (i = 1; i < 4; i++) {
            if (stream_format_code & 0x1)
                bits = 5;
            else
                bits = (chctx->levlCoeffBuf[i] == 16) ? 0 : 5;
            chctx->bitsBandT[i] = bits;
            for (j = band_tab[i]; j < band_tab[i + 1]; j++) {
                chctx->CWlengthT[j] = bits;
                bitscount      += bits;
            }
        }
    }
    if (avctx->codec_id == AV_CODEC_ID_IAC) {
        bitscount += !!chctx->bandWidthT[BANDS - 1];
        if (!(stream_format_code & 0x2))
            bitscount += 16;
    }

    if ((ret = bit_allocation(q, chctx, stream_format_code,
                              512 - bitscount - get_bits_count(&q->gb),
                              flag)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Bit allocations failed\n");
        chctx->decoder_reset = 1;
        return ret;
    }

    if (stream_format_code & 0x1) {
        for (i = 0; i < BANDS; i++)
            chctx->skipFlags[i] = 0;
    } else {
        imc_refine_bit_allocation(q, chctx);
    }

    for (i = 0; i < BANDS; i++) {
        chctx->sumLenArr[i] = 0;

        for (j = band_tab[i]; j < band_tab[i + 1]; j++)
            if (!chctx->skipFlags[j])
                chctx->sumLenArr[i] += chctx->CWlengthT[j];
    }

    memset(chctx->codewords, 0, sizeof(chctx->codewords));

    imc_get_coeffs(avctx, q, chctx);

    if (inverse_quant_coeff(q, chctx, stream_format_code) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Inverse quantization of coefficients failed\n");
        chctx->decoder_reset = 1;
        return AVERROR_INVALIDDATA;
    }

    memset(chctx->skipFlags, 0, sizeof(chctx->skipFlags));

    imc_imdct256(q, chctx, avctx->channels);

    return 0;
}