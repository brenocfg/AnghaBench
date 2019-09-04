#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cpl_in_use; int* new_cpl_coords; int new_cpl_leak; scalar_t__ new_snr_offsets; scalar_t__* channel_in_cpl; scalar_t__ num_rematrixing_bands; scalar_t__ new_rematrixing_strategy; scalar_t__ new_cpl_strategy; } ;
struct TYPE_6__ {scalar_t__ extended_bsi_2; scalar_t__ extended_bsi_1; scalar_t__ audio_production_info; scalar_t__ eac3_info_metadata; scalar_t__ eac3_mixing_metadata; } ;
struct TYPE_5__ {scalar_t__ channel_mode; int num_blocks; int cpl_on; int bitstream_id; int fbw_channels; int num_cpl_subbands; int num_cpl_bands; scalar_t__** exp_strategy; int channels; int frame_bits; int frame_bits_fixed; scalar_t__ eac3; TYPE_3__* blocks; scalar_t__ use_frame_exp_strategy; scalar_t__ lfe_on; scalar_t__ has_surround; scalar_t__ has_center; TYPE_2__ options; } ;
typedef  TYPE_1__ AC3EncodeContext ;
typedef  TYPE_2__ AC3EncOptions ;
typedef  TYPE_3__ AC3Block ;

/* Variables and functions */
 scalar_t__ AC3_CHMODE_2F2R ; 
 scalar_t__ AC3_CHMODE_MONO ; 
 scalar_t__ AC3_CHMODE_STEREO ; 
 scalar_t__ EXP_REUSE ; 

__attribute__((used)) static void count_frame_bits(AC3EncodeContext *s)
{
    AC3EncOptions *opt = &s->options;
    int blk, ch;
    int frame_bits = 0;

    /* header */
    if (s->eac3) {
        if (opt->eac3_mixing_metadata) {
            if (s->channel_mode > AC3_CHMODE_STEREO)
                frame_bits += 2;
            if (s->has_center)
                frame_bits += 6;
            if (s->has_surround)
                frame_bits += 6;
            frame_bits += s->lfe_on;
            frame_bits += 1 + 1 + 2;
            if (s->channel_mode < AC3_CHMODE_STEREO)
                frame_bits++;
            frame_bits++;
        }
        if (opt->eac3_info_metadata) {
            frame_bits += 3 + 1 + 1;
            if (s->channel_mode == AC3_CHMODE_STEREO)
                frame_bits += 2 + 2;
            if (s->channel_mode >= AC3_CHMODE_2F2R)
                frame_bits += 2;
            frame_bits++;
            if (opt->audio_production_info)
                frame_bits += 5 + 2 + 1;
            frame_bits++;
        }
        /* coupling */
        if (s->channel_mode > AC3_CHMODE_MONO) {
            frame_bits++;
            for (blk = 1; blk < s->num_blocks; blk++) {
                AC3Block *block = &s->blocks[blk];
                frame_bits++;
                if (block->new_cpl_strategy)
                    frame_bits++;
            }
        }
        /* coupling exponent strategy */
        if (s->cpl_on) {
            if (s->use_frame_exp_strategy) {
                frame_bits += 5 * s->cpl_on;
            } else {
                for (blk = 0; blk < s->num_blocks; blk++)
                    frame_bits += 2 * s->blocks[blk].cpl_in_use;
            }
        }
    } else {
        if (opt->audio_production_info)
            frame_bits += 7;
        if (s->bitstream_id == 6) {
            if (opt->extended_bsi_1)
                frame_bits += 14;
            if (opt->extended_bsi_2)
                frame_bits += 14;
        }
    }

    /* audio blocks */
    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];

        /* coupling strategy */
        if (!s->eac3)
            frame_bits++;
        if (block->new_cpl_strategy) {
            if (!s->eac3)
                frame_bits++;
            if (block->cpl_in_use) {
                if (s->eac3)
                    frame_bits++;
                if (!s->eac3 || s->channel_mode != AC3_CHMODE_STEREO)
                    frame_bits += s->fbw_channels;
                if (s->channel_mode == AC3_CHMODE_STEREO)
                    frame_bits++;
                frame_bits += 4 + 4;
                if (s->eac3)
                    frame_bits++;
                else
                    frame_bits += s->num_cpl_subbands - 1;
            }
        }

        /* coupling coordinates */
        if (block->cpl_in_use) {
            for (ch = 1; ch <= s->fbw_channels; ch++) {
                if (block->channel_in_cpl[ch]) {
                    if (!s->eac3 || block->new_cpl_coords[ch] != 2)
                        frame_bits++;
                    if (block->new_cpl_coords[ch]) {
                        frame_bits += 2;
                        frame_bits += (4 + 4) * s->num_cpl_bands;
                    }
                }
            }
        }

        /* stereo rematrixing */
        if (s->channel_mode == AC3_CHMODE_STEREO) {
            if (!s->eac3 || blk > 0)
                frame_bits++;
            if (s->blocks[blk].new_rematrixing_strategy)
                frame_bits += block->num_rematrixing_bands;
        }

        /* bandwidth codes & gain range */
        for (ch = 1; ch <= s->fbw_channels; ch++) {
            if (s->exp_strategy[ch][blk] != EXP_REUSE) {
                if (!block->channel_in_cpl[ch])
                    frame_bits += 6;
                frame_bits += 2;
            }
        }

        /* coupling exponent strategy */
        if (!s->eac3 && block->cpl_in_use)
            frame_bits += 2;

        /* snr offsets and fast gain codes */
        if (!s->eac3) {
            frame_bits++;
            if (block->new_snr_offsets)
                frame_bits += 6 + (s->channels + block->cpl_in_use) * (4 + 3);
        }

        /* coupling leak info */
        if (block->cpl_in_use) {
            if (!s->eac3 || block->new_cpl_leak != 2)
                frame_bits++;
            if (block->new_cpl_leak)
                frame_bits += 3 + 3;
        }
    }

    s->frame_bits = s->frame_bits_fixed + frame_bits;
}