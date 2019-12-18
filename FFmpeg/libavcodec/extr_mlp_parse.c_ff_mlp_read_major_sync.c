#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_12__ {int size_in_bits; scalar_t__ buffer; } ;
struct TYPE_11__ {int stream_type; int header_size; int group1_bits; int group1_samplerate; int channel_arrangement; int channel_modifier_thd_stream0; int channel_modifier_thd_stream1; int channel_modifier_thd_stream2; int access_unit_size; int access_unit_size_pow2; int peak_bitrate; int num_substreams; int /*<<< orphan*/  is_vbr; void* channel_layout_thd_stream2; void* channels_thd_stream2; void* channel_layout_thd_stream1; void* channels_thd_stream1; void* group2_samplerate; void* group2_bits; int /*<<< orphan*/  channel_layout_mlp; int /*<<< orphan*/  channels_mlp; } ;
typedef  TYPE_1__ MLPHeaderInfo ;
typedef  TYPE_2__ GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_RL16 (scalar_t__) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ff_mlp_checksum16 (scalar_t__,int) ; 
 int get_bits (TYPE_2__*,int) ; 
 int /*<<< orphan*/  get_bits1 (TYPE_2__*) ; 
 scalar_t__ get_bits_count (TYPE_2__*) ; 
 int get_bits_long (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * mlp_channels ; 
 int mlp_get_major_sync_size (scalar_t__,int) ; 
 int /*<<< orphan*/ * mlp_layout ; 
 void** mlp_quants ; 
 void* mlp_samplerate (int) ; 
 int /*<<< orphan*/  skip_bits (TYPE_2__*,int) ; 
 int /*<<< orphan*/  skip_bits_long (TYPE_2__*,int) ; 
 void* truehd_channels (int) ; 
 void* truehd_layout (int) ; 

int ff_mlp_read_major_sync(void *log, MLPHeaderInfo *mh, GetBitContext *gb)
{
    int ratebits, channel_arrangement, header_size;
    uint16_t checksum;

    av_assert1(get_bits_count(gb) == 0);

    header_size = mlp_get_major_sync_size(gb->buffer, gb->size_in_bits >> 3);
    if (header_size < 0 || gb->size_in_bits < header_size << 3) {
        av_log(log, AV_LOG_ERROR, "packet too short, unable to read major sync\n");
        return -1;
    }

    checksum = ff_mlp_checksum16(gb->buffer, header_size - 2);
    if (checksum != AV_RL16(gb->buffer+header_size-2)) {
        av_log(log, AV_LOG_ERROR, "major sync info header checksum error\n");
        return AVERROR_INVALIDDATA;
    }

    if (get_bits_long(gb, 24) != 0xf8726f) /* Sync words */
        return AVERROR_INVALIDDATA;

    mh->stream_type = get_bits(gb, 8);
    mh->header_size = header_size;

    if (mh->stream_type == 0xbb) {
        mh->group1_bits = mlp_quants[get_bits(gb, 4)];
        mh->group2_bits = mlp_quants[get_bits(gb, 4)];

        ratebits = get_bits(gb, 4);
        mh->group1_samplerate = mlp_samplerate(ratebits);
        mh->group2_samplerate = mlp_samplerate(get_bits(gb, 4));

        skip_bits(gb, 11);

        mh->channel_arrangement=
        channel_arrangement    = get_bits(gb, 5);
        mh->channels_mlp       = mlp_channels[channel_arrangement];
        mh->channel_layout_mlp = mlp_layout[channel_arrangement];
    } else if (mh->stream_type == 0xba) {
        mh->group1_bits = 24; // TODO: Is this information actually conveyed anywhere?
        mh->group2_bits = 0;

        ratebits = get_bits(gb, 4);
        mh->group1_samplerate = mlp_samplerate(ratebits);
        mh->group2_samplerate = 0;

        skip_bits(gb, 4);

        mh->channel_modifier_thd_stream0 = get_bits(gb, 2);
        mh->channel_modifier_thd_stream1 = get_bits(gb, 2);

        mh->channel_arrangement=
        channel_arrangement            = get_bits(gb, 5);
        mh->channels_thd_stream1       = truehd_channels(channel_arrangement);
        mh->channel_layout_thd_stream1 = truehd_layout(channel_arrangement);

        mh->channel_modifier_thd_stream2 = get_bits(gb, 2);

        channel_arrangement            = get_bits(gb, 13);
        mh->channels_thd_stream2       = truehd_channels(channel_arrangement);
        mh->channel_layout_thd_stream2 = truehd_layout(channel_arrangement);
    } else
        return AVERROR_INVALIDDATA;

    mh->access_unit_size = 40 << (ratebits & 7);
    mh->access_unit_size_pow2 = 64 << (ratebits & 7);

    skip_bits_long(gb, 48);

    mh->is_vbr = get_bits1(gb);

    mh->peak_bitrate = (get_bits(gb, 15) * mh->group1_samplerate + 8) >> 4;

    mh->num_substreams = get_bits(gb, 4);

    skip_bits_long(gb, 4 + (header_size - 17) * 8);

    return 0;
}