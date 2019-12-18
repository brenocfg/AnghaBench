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
typedef  int uint8_t ;
struct TYPE_5__ {size_t b1; int* b1_mant; size_t b2; int* b2_mant; int b4; int b4_mant; } ;
typedef  TYPE_1__ mant_groups ;
typedef  int int8_t ;
typedef  int int32_t ;
struct TYPE_6__ {int* start_freq; int* end_freq; int** bap; int** dexps; int** fixed_coeffs; int /*<<< orphan*/  avctx; int /*<<< orphan*/  dith_state; int /*<<< orphan*/  gbc; scalar_t__* dither_flag; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AC3DecodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int CPL_CH ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 void*** b1_mantissas ; 
 void*** b2_mantissas ; 
 int* b3_mantissas ; 
 void*** b4_mantissas ; 
 int* b5_mantissas ; 
 size_t get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_sbits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * quantization_tab ; 

__attribute__((used)) static void ac3_decode_transform_coeffs_ch(AC3DecodeContext *s, int ch_index, mant_groups *m)
{
    int start_freq = s->start_freq[ch_index];
    int end_freq   = s->end_freq[ch_index];
    uint8_t *baps  = s->bap[ch_index];
    int8_t *exps   = s->dexps[ch_index];
    int32_t *coeffs = s->fixed_coeffs[ch_index];
    int dither     = (ch_index == CPL_CH) || s->dither_flag[ch_index];
    GetBitContext *gbc = &s->gbc;
    int freq;

    for (freq = start_freq; freq < end_freq; freq++) {
        int bap = baps[freq];
        int mantissa;
        switch (bap) {
        case 0:
            /* random noise with approximate range of -0.707 to 0.707 */
            if (dither)
                mantissa = (((av_lfg_get(&s->dith_state)>>8)*181)>>8) - 5931008;
            else
                mantissa = 0;
            break;
        case 1:
            if (m->b1) {
                m->b1--;
                mantissa = m->b1_mant[m->b1];
            } else {
                int bits      = get_bits(gbc, 5);
                mantissa      = b1_mantissas[bits][0];
                m->b1_mant[1] = b1_mantissas[bits][1];
                m->b1_mant[0] = b1_mantissas[bits][2];
                m->b1         = 2;
            }
            break;
        case 2:
            if (m->b2) {
                m->b2--;
                mantissa = m->b2_mant[m->b2];
            } else {
                int bits      = get_bits(gbc, 7);
                mantissa      = b2_mantissas[bits][0];
                m->b2_mant[1] = b2_mantissas[bits][1];
                m->b2_mant[0] = b2_mantissas[bits][2];
                m->b2         = 2;
            }
            break;
        case 3:
            mantissa = b3_mantissas[get_bits(gbc, 3)];
            break;
        case 4:
            if (m->b4) {
                m->b4 = 0;
                mantissa = m->b4_mant;
            } else {
                int bits   = get_bits(gbc, 7);
                mantissa   = b4_mantissas[bits][0];
                m->b4_mant = b4_mantissas[bits][1];
                m->b4      = 1;
            }
            break;
        case 5:
            mantissa = b5_mantissas[get_bits(gbc, 4)];
            break;
        default: /* 6 to 15 */
            /* Shift mantissa and sign-extend it. */
            if (bap > 15) {
                av_log(s->avctx, AV_LOG_ERROR, "bap %d is invalid in plain AC-3\n", bap);
                bap = 15;
            }
            mantissa = (unsigned)get_sbits(gbc, quantization_tab[bap]) << (24 - quantization_tab[bap]);
            break;
        }
        coeffs[freq] = mantissa >> exps[freq];
    }
}