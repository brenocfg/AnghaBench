#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int samplerate; int samples_per_frame; int bitrate; int compression_level; int /*<<< orphan*/ * name; int /*<<< orphan*/  dither_method; scalar_t__ normalize_mix_level; scalar_t__ gain; scalar_t__ dynamic_range_compression; int /*<<< orphan*/  mixdown; int /*<<< orphan*/  quality; int /*<<< orphan*/  codec; scalar_t__ track; } ;
struct TYPE_7__ {int samplerate; int samples_per_frame; int bitrate; scalar_t__ track; int /*<<< orphan*/ * channel_map; scalar_t__ channel_layout; int /*<<< orphan*/  matrix_encoding; scalar_t__ sample_bit_depth; scalar_t__ mode; scalar_t__ flags; scalar_t__ version; scalar_t__ substream_type; scalar_t__ stream_type; scalar_t__ reg_desc; scalar_t__ codec_param; scalar_t__ codec; } ;
struct TYPE_6__ {scalar_t__* iso639_2; scalar_t__* simple; scalar_t__* description; } ;
struct TYPE_9__ {TYPE_3__ out; TYPE_2__ in; TYPE_1__ lang; } ;
typedef  TYPE_4__ hb_audio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_MATRIX_ENCODING_NONE ; 
 int /*<<< orphan*/  HB_INVALID_AMIXDOWN ; 
 int /*<<< orphan*/  HB_INVALID_AUDIO_QUALITY ; 
 int /*<<< orphan*/  HB_MUX_MP4 ; 
 int /*<<< orphan*/  hb_audio_dither_get_default () ; 
 int /*<<< orphan*/  hb_audio_encoder_get_default (int /*<<< orphan*/ ) ; 

void hb_audio_config_init(hb_audio_config_t * audiocfg)
{
    /* Set read-only parameters to invalid values */
    audiocfg->in.codec = 0;
    audiocfg->in.codec_param = 0;
    audiocfg->in.reg_desc = 0;
    audiocfg->in.stream_type = 0;
    audiocfg->in.substream_type = 0;
    audiocfg->in.version = 0;
    audiocfg->in.flags = 0;
    audiocfg->in.mode = 0;
    audiocfg->in.samplerate = -1;
    audiocfg->in.sample_bit_depth = 0;
    audiocfg->in.samples_per_frame = -1;
    audiocfg->in.bitrate = -1;
    audiocfg->in.matrix_encoding = AV_MATRIX_ENCODING_NONE;
    audiocfg->in.channel_layout = 0;
    audiocfg->in.channel_map = NULL;
    audiocfg->lang.description[0] = 0;
    audiocfg->lang.simple[0] = 0;
    audiocfg->lang.iso639_2[0] = 0;

    /* Initialize some sensible defaults */
    audiocfg->in.track = audiocfg->out.track = 0;
    audiocfg->out.codec = hb_audio_encoder_get_default(HB_MUX_MP4); // default container
    audiocfg->out.samplerate = -1;
    audiocfg->out.samples_per_frame = -1;
    audiocfg->out.bitrate = -1;
    audiocfg->out.quality = HB_INVALID_AUDIO_QUALITY;
    audiocfg->out.compression_level = -1;
    audiocfg->out.mixdown = HB_INVALID_AMIXDOWN;
    audiocfg->out.dynamic_range_compression = 0;
    audiocfg->out.gain = 0;
    audiocfg->out.normalize_mix_level = 0;
    audiocfg->out.dither_method = hb_audio_dither_get_default();
    audiocfg->out.name = NULL;
}