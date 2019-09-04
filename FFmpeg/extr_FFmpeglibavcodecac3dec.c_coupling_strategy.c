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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int fbw_channels; int channel_mode; int* channel_in_cpl; int spx_src_start_freq; int* start_freq; int* end_freq; int* first_cpl_coords; void* phase_flags_in_use; int /*<<< orphan*/  eac3; int /*<<< orphan*/  first_cpl_leak; int /*<<< orphan*/  cpl_band_struct; int /*<<< orphan*/  cpl_band_sizes; int /*<<< orphan*/  num_cpl_bands; int /*<<< orphan*/  avctx; scalar_t__ spx_in_use; void** cpl_in_use; int /*<<< orphan*/  gbc; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 int AC3_CHMODE_STEREO ; 
 int /*<<< orphan*/  AC3_MAX_CHANNELS ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t CPL_CH ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  decode_band_structure (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_eac3_default_cpl_band_struct ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int coupling_strategy(AC3DecodeContext *s, int blk,
                                    uint8_t *bit_alloc_stages)
{
    GetBitContext *bc = &s->gbc;
    int fbw_channels = s->fbw_channels;
    int channel_mode = s->channel_mode;
    int ch;

    memset(bit_alloc_stages, 3, AC3_MAX_CHANNELS);
    if (!s->eac3)
        s->cpl_in_use[blk] = get_bits1(bc);
    if (s->cpl_in_use[blk]) {
        /* coupling in use */
        int cpl_start_subband, cpl_end_subband;

        if (channel_mode < AC3_CHMODE_STEREO) {
            av_log(s->avctx, AV_LOG_ERROR, "coupling not allowed in mono or dual-mono\n");
            return AVERROR_INVALIDDATA;
        }

        /* check for enhanced coupling */
        if (s->eac3 && get_bits1(bc)) {
            /* TODO: parse enhanced coupling strategy info */
            avpriv_request_sample(s->avctx, "Enhanced coupling");
            return AVERROR_PATCHWELCOME;
        }

        /* determine which channels are coupled */
        if (s->eac3 && s->channel_mode == AC3_CHMODE_STEREO) {
            s->channel_in_cpl[1] = 1;
            s->channel_in_cpl[2] = 1;
        } else {
            for (ch = 1; ch <= fbw_channels; ch++)
                s->channel_in_cpl[ch] = get_bits1(bc);
        }

        /* phase flags in use */
        if (channel_mode == AC3_CHMODE_STEREO)
            s->phase_flags_in_use = get_bits1(bc);

        /* coupling frequency range */
        cpl_start_subband = get_bits(bc, 4);
        cpl_end_subband = s->spx_in_use ? (s->spx_src_start_freq - 37) / 12 :
                                          get_bits(bc, 4) + 3;
        if (cpl_start_subband >= cpl_end_subband) {
            av_log(s->avctx, AV_LOG_ERROR, "invalid coupling range (%d >= %d)\n",
                   cpl_start_subband, cpl_end_subband);
            return AVERROR_INVALIDDATA;
        }
        s->start_freq[CPL_CH] = cpl_start_subband * 12 + 37;
        s->end_freq[CPL_CH]   = cpl_end_subband   * 12 + 37;

        decode_band_structure(bc, blk, s->eac3, 0, cpl_start_subband,
                              cpl_end_subband,
                              ff_eac3_default_cpl_band_struct,
                              &s->num_cpl_bands, s->cpl_band_sizes,
                              s->cpl_band_struct, sizeof(s->cpl_band_struct));
    } else {
        /* coupling not in use */
        for (ch = 1; ch <= fbw_channels; ch++) {
            s->channel_in_cpl[ch] = 0;
            s->first_cpl_coords[ch] = 1;
        }
        s->first_cpl_leak = s->eac3;
        s->phase_flags_in_use = 0;
    }

    return 0;
}