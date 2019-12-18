#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum BandType { ____Placeholder_BandType } BandType ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
struct TYPE_7__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_6__ {int num_window_groups; int max_sfb; } ;
typedef  TYPE_1__ IndividualChannelStream ;
typedef  int INTFLOAT ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AACContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FIXR (int) ; 
 int INTENSITY_BT ; 
 int INTENSITY_BT2 ; 
 int NOISE_BT ; 
 int /*<<< orphan*/  NOISE_OFFSET ; 
 scalar_t__ NOISE_PRE ; 
 int /*<<< orphan*/  NOISE_PRE_BITS ; 
 int POW_SF2_ZERO ; 
 scalar_t__ SCALE_DIFF_ZERO ; 
 int ZERO_BT ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*,int,int) ; 
 int* ff_aac_pow2sf_tab ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__ vlc_scalefactors ; 

__attribute__((used)) static int decode_scalefactors(AACContext *ac, INTFLOAT sf[120], GetBitContext *gb,
                               unsigned int global_gain,
                               IndividualChannelStream *ics,
                               enum BandType band_type[120],
                               int band_type_run_end[120])
{
    int g, i, idx = 0;
    int offset[3] = { global_gain, global_gain - NOISE_OFFSET, 0 };
    int clipped_offset;
    int noise_flag = 1;
    for (g = 0; g < ics->num_window_groups; g++) {
        for (i = 0; i < ics->max_sfb;) {
            int run_end = band_type_run_end[idx];
            if (band_type[idx] == ZERO_BT) {
                for (; i < run_end; i++, idx++)
                    sf[idx] = FIXR(0.);
            } else if ((band_type[idx] == INTENSITY_BT) ||
                       (band_type[idx] == INTENSITY_BT2)) {
                for (; i < run_end; i++, idx++) {
                    offset[2] += get_vlc2(gb, vlc_scalefactors.table, 7, 3) - SCALE_DIFF_ZERO;
                    clipped_offset = av_clip(offset[2], -155, 100);
                    if (offset[2] != clipped_offset) {
                        avpriv_request_sample(ac->avctx,
                                              "If you heard an audible artifact, there may be a bug in the decoder. "
                                              "Clipped intensity stereo position (%d -> %d)",
                                              offset[2], clipped_offset);
                    }
#if USE_FIXED
                    sf[idx] = 100 - clipped_offset;
#else
                    sf[idx] = ff_aac_pow2sf_tab[-clipped_offset + POW_SF2_ZERO];
#endif /* USE_FIXED */
                }
            } else if (band_type[idx] == NOISE_BT) {
                for (; i < run_end; i++, idx++) {
                    if (noise_flag-- > 0)
                        offset[1] += get_bits(gb, NOISE_PRE_BITS) - NOISE_PRE;
                    else
                        offset[1] += get_vlc2(gb, vlc_scalefactors.table, 7, 3) - SCALE_DIFF_ZERO;
                    clipped_offset = av_clip(offset[1], -100, 155);
                    if (offset[1] != clipped_offset) {
                        avpriv_request_sample(ac->avctx,
                                              "If you heard an audible artifact, there may be a bug in the decoder. "
                                              "Clipped noise gain (%d -> %d)",
                                              offset[1], clipped_offset);
                    }
#if USE_FIXED
                    sf[idx] = -(100 + clipped_offset);
#else
                    sf[idx] = -ff_aac_pow2sf_tab[clipped_offset + POW_SF2_ZERO];
#endif /* USE_FIXED */
                }
            } else {
                for (; i < run_end; i++, idx++) {
                    offset[0] += get_vlc2(gb, vlc_scalefactors.table, 7, 3) - SCALE_DIFF_ZERO;
                    if (offset[0] > 255U) {
                        av_log(ac->avctx, AV_LOG_ERROR,
                               "Scalefactor (%d) out of range.\n", offset[0]);
                        return AVERROR_INVALIDDATA;
                    }
#if USE_FIXED
                    sf[idx] = -offset[0];
#else
                    sf[idx] = -ff_aac_pow2sf_tab[offset[0] - 100 + POW_SF2_ZERO];
#endif /* USE_FIXED */
                }
            }
        }
    }
    return 0;
}