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
struct TYPE_3__ {size_t audio_mode; int ext_audio_mask; unsigned int xxch_core_mask; int xxch_mask_nbits; unsigned int xxch_spkr_mask; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int DCA_CSS_XCH ; 
 int DCA_CSS_XXCH ; 
 int DCA_EXSS_XXCH ; 
 int DCA_SPEAKER_Cs ; 
 int DCA_SPEAKER_Ls ; 
 int DCA_SPEAKER_Lss ; 
 int DCA_SPEAKER_MASK_Lss ; 
 int DCA_SPEAKER_MASK_Rss ; 
 int DCA_SPEAKER_Rs ; 
 int DCA_SPEAKER_Rss ; 
 int* ff_dca_channels ; 
 int** prm_ch_to_spkr_map ; 

__attribute__((used)) static int map_prm_ch_to_spkr(DCACoreDecoder *s, int ch)
{
    int pos, spkr;

    // Try to map this channel to core first
    pos = ff_dca_channels[s->audio_mode];
    if (ch < pos) {
        spkr = prm_ch_to_spkr_map[s->audio_mode][ch];
        if (s->ext_audio_mask & (DCA_CSS_XXCH | DCA_EXSS_XXCH)) {
            if (s->xxch_core_mask & (1U << spkr))
                return spkr;
            if (spkr == DCA_SPEAKER_Ls && (s->xxch_core_mask & DCA_SPEAKER_MASK_Lss))
                return DCA_SPEAKER_Lss;
            if (spkr == DCA_SPEAKER_Rs && (s->xxch_core_mask & DCA_SPEAKER_MASK_Rss))
                return DCA_SPEAKER_Rss;
            return -1;
        }
        return spkr;
    }

    // Then XCH
    if ((s->ext_audio_mask & DCA_CSS_XCH) && ch == pos)
        return DCA_SPEAKER_Cs;

    // Then XXCH
    if (s->ext_audio_mask & (DCA_CSS_XXCH | DCA_EXSS_XXCH)) {
        for (spkr = DCA_SPEAKER_Cs; spkr < s->xxch_mask_nbits; spkr++)
            if (s->xxch_spkr_mask & (1U << spkr))
                if (pos++ == ch)
                    return spkr;
    }

    // No mapping
    return -1;
}