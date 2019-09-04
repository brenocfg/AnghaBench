#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_DATA_PARAM_CHANGE ; 
 int AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_COUNT ; 
 int AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_LAYOUT ; 
 int AV_SIDE_DATA_PARAM_CHANGE_DIMENSIONS ; 
 int AV_SIDE_DATA_PARAM_CHANGE_SAMPLE_RATE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_packet_new_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  bytestream_put_le64 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int ff_add_param_change(AVPacket *pkt, int32_t channels,
                        uint64_t channel_layout, int32_t sample_rate,
                        int32_t width, int32_t height)
{
    uint32_t flags = 0;
    int size = 4;
    uint8_t *data;
    if (!pkt)
        return AVERROR(EINVAL);
    if (channels) {
        size  += 4;
        flags |= AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_COUNT;
    }
    if (channel_layout) {
        size  += 8;
        flags |= AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_LAYOUT;
    }
    if (sample_rate) {
        size  += 4;
        flags |= AV_SIDE_DATA_PARAM_CHANGE_SAMPLE_RATE;
    }
    if (width || height) {
        size  += 8;
        flags |= AV_SIDE_DATA_PARAM_CHANGE_DIMENSIONS;
    }
    data = av_packet_new_side_data(pkt, AV_PKT_DATA_PARAM_CHANGE, size);
    if (!data)
        return AVERROR(ENOMEM);
    bytestream_put_le32(&data, flags);
    if (channels)
        bytestream_put_le32(&data, channels);
    if (channel_layout)
        bytestream_put_le64(&data, channel_layout);
    if (sample_rate)
        bytestream_put_le32(&data, sample_rate);
    if (width || height) {
        bytestream_put_le32(&data, width);
        bytestream_put_le32(&data, height);
    }
    return 0;
}