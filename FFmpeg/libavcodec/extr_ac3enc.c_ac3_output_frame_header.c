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
struct TYPE_7__ {int dolby_surround_mode; int dialogue_level; int audio_production_info; int mixing_level; int room_type; int copyright; int original; int extended_bsi_1; int preferred_stereo_downmix; int extended_bsi_2; int dolby_surround_ex_mode; int dolby_headphone_mode; int ad_converter_type; } ;
struct TYPE_5__ {int sr_code; } ;
struct TYPE_6__ {int frame_size_code; int frame_size; int frame_size_min; int bitstream_id; int bitstream_mode; int channel_mode; int center_mix_level; int surround_mix_level; int lfe_on; int ltrt_center_mix_level; int ltrt_surround_mix_level; int loro_center_mix_level; int loro_surround_mix_level; int /*<<< orphan*/  pb; TYPE_1__ bit_alloc; TYPE_3__ options; } ;
typedef  TYPE_2__ AC3EncodeContext ;
typedef  TYPE_3__ AC3EncOptions ;

/* Variables and functions */
 int AC3_CHMODE_MONO ; 
 int AC3_CHMODE_STEREO ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void ac3_output_frame_header(AC3EncodeContext *s)
{
    AC3EncOptions *opt = &s->options;

    put_bits(&s->pb, 16, 0x0b77);   /* frame header */
    put_bits(&s->pb, 16, 0);        /* crc1: will be filled later */
    put_bits(&s->pb, 2,  s->bit_alloc.sr_code);
    put_bits(&s->pb, 6,  s->frame_size_code + (s->frame_size - s->frame_size_min) / 2);
    put_bits(&s->pb, 5,  s->bitstream_id);
    put_bits(&s->pb, 3,  s->bitstream_mode);
    put_bits(&s->pb, 3,  s->channel_mode);
    if ((s->channel_mode & 0x01) && s->channel_mode != AC3_CHMODE_MONO)
        put_bits(&s->pb, 2, s->center_mix_level);
    if (s->channel_mode & 0x04)
        put_bits(&s->pb, 2, s->surround_mix_level);
    if (s->channel_mode == AC3_CHMODE_STEREO)
        put_bits(&s->pb, 2, opt->dolby_surround_mode);
    put_bits(&s->pb, 1, s->lfe_on); /* LFE */
    put_bits(&s->pb, 5, -opt->dialogue_level);
    put_bits(&s->pb, 1, 0);         /* no compression control word */
    put_bits(&s->pb, 1, 0);         /* no lang code */
    put_bits(&s->pb, 1, opt->audio_production_info);
    if (opt->audio_production_info) {
        put_bits(&s->pb, 5, opt->mixing_level - 80);
        put_bits(&s->pb, 2, opt->room_type);
    }
    put_bits(&s->pb, 1, opt->copyright);
    put_bits(&s->pb, 1, opt->original);
    if (s->bitstream_id == 6) {
        /* alternate bit stream syntax */
        put_bits(&s->pb, 1, opt->extended_bsi_1);
        if (opt->extended_bsi_1) {
            put_bits(&s->pb, 2, opt->preferred_stereo_downmix);
            put_bits(&s->pb, 3, s->ltrt_center_mix_level);
            put_bits(&s->pb, 3, s->ltrt_surround_mix_level);
            put_bits(&s->pb, 3, s->loro_center_mix_level);
            put_bits(&s->pb, 3, s->loro_surround_mix_level);
        }
        put_bits(&s->pb, 1, opt->extended_bsi_2);
        if (opt->extended_bsi_2) {
            put_bits(&s->pb, 2, opt->dolby_surround_ex_mode);
            put_bits(&s->pb, 2, opt->dolby_headphone_mode);
            put_bits(&s->pb, 1, opt->ad_converter_type);
            put_bits(&s->pb, 9, 0);     /* xbsi2 and encinfo : reserved */
        }
    } else {
    put_bits(&s->pb, 1, 0);         /* no time code 1 */
    put_bits(&s->pb, 1, 0);         /* no time code 2 */
    }
    put_bits(&s->pb, 1, 0);         /* no additional bit stream info */
}