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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int channels; scalar_t__ sample_rate; int /*<<< orphan*/  frame_samples; int /*<<< orphan*/  ch_layout; scalar_t__ bps; void* data_type; int /*<<< orphan*/  samples; void* codec; } ;
typedef  TYPE_1__ TAKStreamInfo ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 scalar_t__ TAK_BPS_MIN ; 
 int TAK_CHANNELS_MIN ; 
 int /*<<< orphan*/  TAK_ENCODER_CODEC_BITS ; 
 int /*<<< orphan*/  TAK_ENCODER_PROFILE_BITS ; 
 int /*<<< orphan*/  TAK_FORMAT_BPS_BITS ; 
 int /*<<< orphan*/  TAK_FORMAT_CHANNEL_BITS ; 
 int /*<<< orphan*/  TAK_FORMAT_CH_LAYOUT_BITS ; 
 int /*<<< orphan*/  TAK_FORMAT_DATA_TYPE_BITS ; 
 int /*<<< orphan*/  TAK_FORMAT_SAMPLE_RATE_BITS ; 
 int /*<<< orphan*/  TAK_FORMAT_VALID_BITS ; 
 scalar_t__ TAK_SAMPLE_RATE_MIN ; 
 int /*<<< orphan*/  TAK_SIZE_FRAME_DURATION_BITS ; 
 int /*<<< orphan*/  TAK_SIZE_SAMPLES_NUM_BITS ; 
 void* get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tak_channel_layouts ; 
 int /*<<< orphan*/  tak_get_nb_samples (scalar_t__,int) ; 

void ff_tak_parse_streaminfo(TAKStreamInfo *s, GetBitContext *gb)
{
    uint64_t channel_mask = 0;
    int frame_type, i;

    s->codec = get_bits(gb, TAK_ENCODER_CODEC_BITS);
    skip_bits(gb, TAK_ENCODER_PROFILE_BITS);

    frame_type = get_bits(gb, TAK_SIZE_FRAME_DURATION_BITS);
    s->samples = get_bits64(gb, TAK_SIZE_SAMPLES_NUM_BITS);

    s->data_type   = get_bits(gb, TAK_FORMAT_DATA_TYPE_BITS);
    s->sample_rate = get_bits(gb, TAK_FORMAT_SAMPLE_RATE_BITS) +
                     TAK_SAMPLE_RATE_MIN;
    s->bps         = get_bits(gb, TAK_FORMAT_BPS_BITS) +
                     TAK_BPS_MIN;
    s->channels    = get_bits(gb, TAK_FORMAT_CHANNEL_BITS) +
                     TAK_CHANNELS_MIN;

    if (get_bits1(gb)) {
        skip_bits(gb, TAK_FORMAT_VALID_BITS);
        if (get_bits1(gb)) {
            for (i = 0; i < s->channels; i++) {
                int value = get_bits(gb, TAK_FORMAT_CH_LAYOUT_BITS);

                if (value < FF_ARRAY_ELEMS(tak_channel_layouts))
                    channel_mask |= tak_channel_layouts[value];
            }
        }
    }

    s->ch_layout     = channel_mask;
    s->frame_samples = tak_get_nb_samples(s->sample_rate, frame_type);
}