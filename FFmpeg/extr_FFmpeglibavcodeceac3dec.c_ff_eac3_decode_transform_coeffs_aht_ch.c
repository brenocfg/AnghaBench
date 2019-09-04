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
typedef  int int64_t ;
struct TYPE_3__ {int* start_freq; int* end_freq; int** bap; int*** pre_mantissa; int /*<<< orphan*/  dith_state; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gbc; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 int AC3_MAX_COEFS ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int EAC3_GAQ_12 ; 
 int EAC3_GAQ_124 ; 
 int EAC3_GAQ_14 ; 
 int EAC3_GAQ_NO ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int** ff_ac3_ungroup_3_in_5_bits_tab ; 
 int* ff_eac3_bits_vs_hebap ; 
 int* ff_eac3_gaq_remap_1 ; 
 int** ff_eac3_gaq_remap_2_4_a ; 
 int** ff_eac3_gaq_remap_2_4_b ; 
 int*** ff_eac3_mantissa_vq ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_sbits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idct6 (int*) ; 

__attribute__((used)) static void ff_eac3_decode_transform_coeffs_aht_ch(AC3DecodeContext *s, int ch)
{
    int bin, blk, gs;
    int end_bap, gaq_mode;
    GetBitContext *gbc = &s->gbc;
    int gaq_gain[AC3_MAX_COEFS];

    gaq_mode = get_bits(gbc, 2);
    end_bap = (gaq_mode < 2) ? 12 : 17;

    /* if GAQ gain is used, decode gain codes for bins with hebap between
       8 and end_bap */
    gs = 0;
    if (gaq_mode == EAC3_GAQ_12 || gaq_mode == EAC3_GAQ_14) {
        /* read 1-bit GAQ gain codes */
        for (bin = s->start_freq[ch]; bin < s->end_freq[ch]; bin++) {
            if (s->bap[ch][bin] > 7 && s->bap[ch][bin] < end_bap)
                gaq_gain[gs++] = get_bits1(gbc) << (gaq_mode-1);
        }
    } else if (gaq_mode == EAC3_GAQ_124) {
        /* read 1.67-bit GAQ gain codes (3 codes in 5 bits) */
        int gc = 2;
        for (bin = s->start_freq[ch]; bin < s->end_freq[ch]; bin++) {
            if (s->bap[ch][bin] > 7 && s->bap[ch][bin] < 17) {
                if (gc++ == 2) {
                    int group_code = get_bits(gbc, 5);
                    if (group_code > 26) {
                        av_log(s->avctx, AV_LOG_WARNING, "GAQ gain group code out-of-range\n");
                        group_code = 26;
                    }
                    gaq_gain[gs++] = ff_ac3_ungroup_3_in_5_bits_tab[group_code][0];
                    gaq_gain[gs++] = ff_ac3_ungroup_3_in_5_bits_tab[group_code][1];
                    gaq_gain[gs++] = ff_ac3_ungroup_3_in_5_bits_tab[group_code][2];
                    gc = 0;
                }
            }
        }
    }

    gs=0;
    for (bin = s->start_freq[ch]; bin < s->end_freq[ch]; bin++) {
        int hebap = s->bap[ch][bin];
        int bits = ff_eac3_bits_vs_hebap[hebap];
        if (!hebap) {
            /* zero-mantissa dithering */
            for (blk = 0; blk < 6; blk++) {
                s->pre_mantissa[ch][bin][blk] = (av_lfg_get(&s->dith_state) & 0x7FFFFF) - 0x400000;
            }
        } else if (hebap < 8) {
            /* Vector Quantization */
            int v = get_bits(gbc, bits);
            for (blk = 0; blk < 6; blk++) {
                s->pre_mantissa[ch][bin][blk] = ff_eac3_mantissa_vq[hebap][v][blk] * (1 << 8);
            }
        } else {
            /* Gain Adaptive Quantization */
            int gbits, log_gain;
            if (gaq_mode != EAC3_GAQ_NO && hebap < end_bap) {
                log_gain = gaq_gain[gs++];
            } else {
                log_gain = 0;
            }
            gbits = bits - log_gain;

            for (blk = 0; blk < 6; blk++) {
                int mant = get_sbits(gbc, gbits);
                if (log_gain && mant == -(1 << (gbits-1))) {
                    /* large mantissa */
                    int b;
                    int mbits = bits - (2 - log_gain);
                    mant = get_sbits(gbc, mbits);
                    mant = ((unsigned)mant) << (23 - (mbits - 1));
                    /* remap mantissa value to correct for asymmetric quantization */
                    if (mant >= 0)
                        b = 1 << (23 - log_gain);
                    else
                        b = ff_eac3_gaq_remap_2_4_b[hebap-8][log_gain-1] * (1 << 8);
                    mant += ((ff_eac3_gaq_remap_2_4_a[hebap-8][log_gain-1] * (int64_t)mant) >> 15) + b;
                } else {
                    /* small mantissa, no GAQ, or Gk=1 */
                    mant *= (1 << 24 - bits);
                    if (!log_gain) {
                        /* remap mantissa value for no GAQ or Gk=1 */
                        mant += (ff_eac3_gaq_remap_1[hebap-8] * (int64_t)mant) >> 15;
                    }
                }
                s->pre_mantissa[ch][bin][blk] = mant;
            }
        }
        idct6(s->pre_mantissa[ch][bin]);
    }
}