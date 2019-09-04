#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int cpl_in_use; int new_cpl_strategy; } ;
struct TYPE_10__ {int dialogue_level; int eac3_mixing_metadata; int preferred_stereo_downmix; int eac3_info_metadata; int copyright; int original; int dolby_surround_mode; int dolby_headphone_mode; int dolby_surround_ex_mode; int audio_production_info; int mixing_level; int room_type; int ad_converter_type; } ;
struct TYPE_8__ {int sr_code; scalar_t__ sr_shift; } ;
struct TYPE_9__ {int frame_size; int num_blks_code; int channel_mode; int lfe_on; int bitstream_id; int ltrt_center_mix_level; int loro_center_mix_level; int ltrt_surround_mix_level; int loro_surround_mix_level; int bitstream_mode; int num_blocks; int fbw_channels; int* frame_exp_strategy; int** exp_strategy; size_t lfe_channel; int coarse_snr_offset; int* fine_snr_offset; int /*<<< orphan*/  pb; scalar_t__ use_frame_exp_strategy; TYPE_5__* blocks; int /*<<< orphan*/  cpl_on; TYPE_1__* avctx; scalar_t__ has_surround; scalar_t__ has_center; TYPE_2__ bit_alloc; TYPE_4__ options; } ;
struct TYPE_7__ {int frame_number; } ;
typedef  TYPE_3__ AC3EncodeContext ;
typedef  TYPE_4__ AC3EncOptions ;
typedef  TYPE_5__ AC3Block ;

/* Variables and functions */
 int AC3_CHMODE_2F2R ; 
 int AC3_CHMODE_MONO ; 
 int AC3_CHMODE_STEREO ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

void ff_eac3_output_frame_header(AC3EncodeContext *s)
{
    int blk, ch;
    AC3EncOptions *opt = &s->options;

    put_bits(&s->pb, 16, 0x0b77);                   /* sync word */

    /* BSI header */
    put_bits(&s->pb,  2, 0);                        /* stream type = independent */
    put_bits(&s->pb,  3, 0);                        /* substream id = 0 */
    put_bits(&s->pb, 11, (s->frame_size / 2) - 1);  /* frame size */
    if (s->bit_alloc.sr_shift) {
        put_bits(&s->pb, 2, 0x3);                   /* fscod2 */
        put_bits(&s->pb, 2, s->bit_alloc.sr_code);  /* sample rate code */
    } else {
        put_bits(&s->pb, 2, s->bit_alloc.sr_code);  /* sample rate code */
        put_bits(&s->pb, 2, s->num_blks_code);      /* number of blocks */
    }
    put_bits(&s->pb, 3, s->channel_mode);           /* audio coding mode */
    put_bits(&s->pb, 1, s->lfe_on);                 /* LFE channel indicator */
    put_bits(&s->pb, 5, s->bitstream_id);           /* bitstream id (EAC3=16) */
    put_bits(&s->pb, 5, -opt->dialogue_level);      /* dialogue normalization level */
    put_bits(&s->pb, 1, 0);                         /* no compression gain */
    /* mixing metadata*/
    put_bits(&s->pb, 1, opt->eac3_mixing_metadata);
    if (opt->eac3_mixing_metadata) {
        if (s->channel_mode > AC3_CHMODE_STEREO)
            put_bits(&s->pb, 2, opt->preferred_stereo_downmix);
        if (s->has_center) {
            put_bits(&s->pb, 3, s->ltrt_center_mix_level);
            put_bits(&s->pb, 3, s->loro_center_mix_level);
        }
        if (s->has_surround) {
            put_bits(&s->pb, 3, s->ltrt_surround_mix_level);
            put_bits(&s->pb, 3, s->loro_surround_mix_level);
        }
        if (s->lfe_on)
            put_bits(&s->pb, 1, 0);
        put_bits(&s->pb, 1, 0);                     /* no program scale */
        put_bits(&s->pb, 1, 0);                     /* no ext program scale */
        put_bits(&s->pb, 2, 0);                     /* no mixing parameters */
        if (s->channel_mode < AC3_CHMODE_STEREO)
            put_bits(&s->pb, 1, 0);                 /* no pan info */
        put_bits(&s->pb, 1, 0);                     /* no frame mix config info */
    }
    /* info metadata*/
    put_bits(&s->pb, 1, opt->eac3_info_metadata);
    if (opt->eac3_info_metadata) {
        put_bits(&s->pb, 3, s->bitstream_mode);
        put_bits(&s->pb, 1, opt->copyright);
        put_bits(&s->pb, 1, opt->original);
        if (s->channel_mode == AC3_CHMODE_STEREO) {
            put_bits(&s->pb, 2, opt->dolby_surround_mode);
            put_bits(&s->pb, 2, opt->dolby_headphone_mode);
        }
        if (s->channel_mode >= AC3_CHMODE_2F2R)
            put_bits(&s->pb, 2, opt->dolby_surround_ex_mode);
        put_bits(&s->pb, 1, opt->audio_production_info);
        if (opt->audio_production_info) {
            put_bits(&s->pb, 5, opt->mixing_level - 80);
            put_bits(&s->pb, 2, opt->room_type);
            put_bits(&s->pb, 1, opt->ad_converter_type);
        }
        put_bits(&s->pb, 1, 0);
    }
    if (s->num_blocks != 6)
        put_bits(&s->pb, 1, !(s->avctx->frame_number % 6)); /* converter sync flag */
    put_bits(&s->pb, 1, 0);                         /* no additional bit stream info */

    /* frame header */
    if (s->num_blocks == 6) {
    put_bits(&s->pb, 1, !s->use_frame_exp_strategy);/* exponent strategy syntax */
    put_bits(&s->pb, 1, 0);                         /* aht enabled = no */
    }
    put_bits(&s->pb, 2, 0);                         /* snr offset strategy = 1 */
    put_bits(&s->pb, 1, 0);                         /* transient pre-noise processing enabled = no */
    put_bits(&s->pb, 1, 0);                         /* block switch syntax enabled = no */
    put_bits(&s->pb, 1, 0);                         /* dither flag syntax enabled = no */
    put_bits(&s->pb, 1, 0);                         /* bit allocation model syntax enabled = no */
    put_bits(&s->pb, 1, 0);                         /* fast gain codes enabled = no */
    put_bits(&s->pb, 1, 0);                         /* dba syntax enabled = no */
    put_bits(&s->pb, 1, 0);                         /* skip field syntax enabled = no */
    put_bits(&s->pb, 1, 0);                         /* spx enabled = no */
    /* coupling strategy use flags */
    if (s->channel_mode > AC3_CHMODE_MONO) {
        put_bits(&s->pb, 1, s->blocks[0].cpl_in_use);
        for (blk = 1; blk < s->num_blocks; blk++) {
            AC3Block *block = &s->blocks[blk];
            put_bits(&s->pb, 1, block->new_cpl_strategy);
            if (block->new_cpl_strategy)
                put_bits(&s->pb, 1, block->cpl_in_use);
        }
    }
    /* exponent strategy */
    if (s->use_frame_exp_strategy) {
        for (ch = !s->cpl_on; ch <= s->fbw_channels; ch++)
            put_bits(&s->pb, 5, s->frame_exp_strategy[ch]);
    } else {
        for (blk = 0; blk < s->num_blocks; blk++)
            for (ch = !s->blocks[blk].cpl_in_use; ch <= s->fbw_channels; ch++)
                put_bits(&s->pb, 2, s->exp_strategy[ch][blk]);
    }
    if (s->lfe_on) {
        for (blk = 0; blk < s->num_blocks; blk++)
            put_bits(&s->pb, 1, s->exp_strategy[s->lfe_channel][blk]);
    }
    /* E-AC-3 to AC-3 converter exponent strategy (not optional when num blocks == 6) */
    if (s->num_blocks != 6) {
        put_bits(&s->pb, 1, 0);
    } else {
    for (ch = 1; ch <= s->fbw_channels; ch++) {
        if (s->use_frame_exp_strategy)
            put_bits(&s->pb, 5, s->frame_exp_strategy[ch]);
        else
            put_bits(&s->pb, 5, 0);
    }
    }
    /* snr offsets */
    put_bits(&s->pb, 6, s->coarse_snr_offset);
    put_bits(&s->pb, 4, s->fine_snr_offset[1]);
    /* block start info */
    if (s->num_blocks > 1)
        put_bits(&s->pb, 1, 0);
}