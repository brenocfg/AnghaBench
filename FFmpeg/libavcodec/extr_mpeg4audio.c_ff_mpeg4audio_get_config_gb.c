#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ object_type; int chan_config; int channels; int sbr; int ps; scalar_t__ ext_object_type; int ext_chan_config; void* sample_rate; void* ext_sample_rate; int /*<<< orphan*/  ext_sampling_index; int /*<<< orphan*/  sampling_index; } ;
typedef  TYPE_1__ MPEG4AudioConfig ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ AOT_AAC_LC ; 
 scalar_t__ AOT_ALS ; 
 scalar_t__ AOT_ER_BSAC ; 
 scalar_t__ AOT_NULL ; 
 scalar_t__ AOT_PS ; 
 scalar_t__ AOT_SBR ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_ARRAY_ELEMS (int*) ; 
 scalar_t__ MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,size_t) ; 
 int* ff_mpeg4audio_channels ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 void* get_object_type (int /*<<< orphan*/ *) ; 
 void* get_sample_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parse_config_ALS (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

int ff_mpeg4audio_get_config_gb(MPEG4AudioConfig *c, GetBitContext *gb,
                                int sync_extension, void *logctx)
{
    int specific_config_bitindex, ret;
    int start_bit_index = get_bits_count(gb);
    c->object_type = get_object_type(gb);
    c->sample_rate = get_sample_rate(gb, &c->sampling_index);
    c->chan_config = get_bits(gb, 4);
    if (c->chan_config < FF_ARRAY_ELEMS(ff_mpeg4audio_channels))
        c->channels = ff_mpeg4audio_channels[c->chan_config];
    else {
        av_log(logctx, AV_LOG_ERROR, "Invalid chan_config %d\n", c->chan_config);
        return AVERROR_INVALIDDATA;
    }
    c->sbr = -1;
    c->ps  = -1;
    if (c->object_type == AOT_SBR || (c->object_type == AOT_PS &&
        // check for W6132 Annex YYYY draft MP3onMP4
        !(show_bits(gb, 3) & 0x03 && !(show_bits(gb, 9) & 0x3F)))) {
        if (c->object_type == AOT_PS)
            c->ps = 1;
        c->ext_object_type = AOT_SBR;
        c->sbr = 1;
        c->ext_sample_rate = get_sample_rate(gb, &c->ext_sampling_index);
        c->object_type = get_object_type(gb);
        if (c->object_type == AOT_ER_BSAC)
            c->ext_chan_config = get_bits(gb, 4);
    } else {
        c->ext_object_type = AOT_NULL;
        c->ext_sample_rate = 0;
    }
    specific_config_bitindex = get_bits_count(gb);

    if (c->object_type == AOT_ALS) {
        skip_bits(gb, 5);
        if (show_bits_long(gb, 24) != MKBETAG('\0','A','L','S'))
            skip_bits_long(gb, 24);

        specific_config_bitindex = get_bits_count(gb);

        ret = parse_config_ALS(gb, c);
        if (ret < 0)
            return ret;
    }

    if (c->ext_object_type != AOT_SBR && sync_extension) {
        while (get_bits_left(gb) > 15) {
            if (show_bits(gb, 11) == 0x2b7) { // sync extension
                get_bits(gb, 11);
                c->ext_object_type = get_object_type(gb);
                if (c->ext_object_type == AOT_SBR && (c->sbr = get_bits1(gb)) == 1) {
                    c->ext_sample_rate = get_sample_rate(gb, &c->ext_sampling_index);
                    if (c->ext_sample_rate == c->sample_rate)
                        c->sbr = -1;
                }
                if (get_bits_left(gb) > 11 && get_bits(gb, 11) == 0x548)
                    c->ps = get_bits1(gb);
                break;
            } else
                get_bits1(gb); // skip 1 bit
        }
    }

    //PS requires SBR
    if (!c->sbr)
        c->ps = 0;
    //Limit implicit PS to the HE-AACv2 Profile
    if ((c->ps == -1 && c->object_type != AOT_AAC_LC) || c->channels & ~0x01)
        c->ps = 0;

    return specific_config_bitindex - start_bit_index;
}