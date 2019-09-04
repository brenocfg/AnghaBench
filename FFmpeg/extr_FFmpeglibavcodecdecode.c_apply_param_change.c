#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {int err_recognition; scalar_t__ height; scalar_t__ width; scalar_t__ sample_rate; int /*<<< orphan*/  channel_layout; scalar_t__ channels; TYPE_1__* codec; } ;
struct TYPE_6__ {int capabilities; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_CODEC_CAP_PARAM_CHANGE ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_PARAM_CHANGE ; 
 int AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_COUNT ; 
 int AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_LAYOUT ; 
 int AV_SIDE_DATA_PARAM_CHANGE_DIMENSIONS ; 
 int AV_SIDE_DATA_PARAM_CHANGE_SAMPLE_RATE ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ bytestream_get_le32 (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  bytestream_get_le64 (int /*<<< orphan*/  const**) ; 
 int ff_set_dimensions (TYPE_2__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int apply_param_change(AVCodecContext *avctx, const AVPacket *avpkt)
{
    int size = 0, ret;
    const uint8_t *data;
    uint32_t flags;
    int64_t val;

    data = av_packet_get_side_data(avpkt, AV_PKT_DATA_PARAM_CHANGE, &size);
    if (!data)
        return 0;

    if (!(avctx->codec->capabilities & AV_CODEC_CAP_PARAM_CHANGE)) {
        av_log(avctx, AV_LOG_ERROR, "This decoder does not support parameter "
               "changes, but PARAM_CHANGE side data was sent to it.\n");
        ret = AVERROR(EINVAL);
        goto fail2;
    }

    if (size < 4)
        goto fail;

    flags = bytestream_get_le32(&data);
    size -= 4;

    if (flags & AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_COUNT) {
        if (size < 4)
            goto fail;
        val = bytestream_get_le32(&data);
        if (val <= 0 || val > INT_MAX) {
            av_log(avctx, AV_LOG_ERROR, "Invalid channel count");
            ret = AVERROR_INVALIDDATA;
            goto fail2;
        }
        avctx->channels = val;
        size -= 4;
    }
    if (flags & AV_SIDE_DATA_PARAM_CHANGE_CHANNEL_LAYOUT) {
        if (size < 8)
            goto fail;
        avctx->channel_layout = bytestream_get_le64(&data);
        size -= 8;
    }
    if (flags & AV_SIDE_DATA_PARAM_CHANGE_SAMPLE_RATE) {
        if (size < 4)
            goto fail;
        val = bytestream_get_le32(&data);
        if (val <= 0 || val > INT_MAX) {
            av_log(avctx, AV_LOG_ERROR, "Invalid sample rate");
            ret = AVERROR_INVALIDDATA;
            goto fail2;
        }
        avctx->sample_rate = val;
        size -= 4;
    }
    if (flags & AV_SIDE_DATA_PARAM_CHANGE_DIMENSIONS) {
        if (size < 8)
            goto fail;
        avctx->width  = bytestream_get_le32(&data);
        avctx->height = bytestream_get_le32(&data);
        size -= 8;
        ret = ff_set_dimensions(avctx, avctx->width, avctx->height);
        if (ret < 0)
            goto fail2;
    }

    return 0;
fail:
    av_log(avctx, AV_LOG_ERROR, "PARAM_CHANGE side data too small.\n");
    ret = AVERROR_INVALIDDATA;
fail2:
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error applying parameter changes.\n");
        if (avctx->err_recognition & AV_EF_EXPLODE)
            return ret;
    }
    return 0;
}