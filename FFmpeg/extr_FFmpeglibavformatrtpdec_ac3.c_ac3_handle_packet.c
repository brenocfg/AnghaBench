#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  stream_index; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; } ;
struct TYPE_9__ {int last_frame; unsigned int nr_frames; int /*<<< orphan*/  fragment; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int RTP_AC3_PAYLOAD_HEADER_SIZE ; 
 int RTP_FLAG_MARKER ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_new_packet (TYPE_3__*,int) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int const*,int) ; 
 int ff_rtp_finalize_packet (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static int ac3_handle_packet(AVFormatContext *ctx, PayloadContext *data,
                             AVStream *st, AVPacket *pkt, uint32_t *timestamp,
                             const uint8_t *buf, int len, uint16_t seq,
                             int flags)
{
    unsigned frame_type;
    unsigned nr_frames;
    int err;

    if (len < RTP_AC3_PAYLOAD_HEADER_SIZE + 1) {
        av_log(ctx, AV_LOG_ERROR, "Invalid %d bytes packet\n", len);
        return AVERROR_INVALIDDATA;
    }

    frame_type = buf[0] & 0x3;
    nr_frames = buf[1];
    buf += RTP_AC3_PAYLOAD_HEADER_SIZE;
    len -= RTP_AC3_PAYLOAD_HEADER_SIZE;

    switch (frame_type) {
    case 0: /* One or more complete frames */
        if (!nr_frames) {
            av_log(ctx, AV_LOG_ERROR, "Invalid AC3 packet data\n");
            return AVERROR_INVALIDDATA;
        }
        if (av_new_packet(pkt, len)) {
            av_log(ctx, AV_LOG_ERROR, "Out of memory.\n");
            return AVERROR(ENOMEM);
        }

        pkt->stream_index = st->index;
        memcpy(pkt->data, buf, len);
        return 0;

    case 1:
    case 2: /* First fragment */
        ffio_free_dyn_buf(&data->fragment);

        data->last_frame = 1;
        data->nr_frames = nr_frames;
        err = avio_open_dyn_buf(&data->fragment);
        if (err < 0)
            return err;

        avio_write(data->fragment, buf, len);
        data->timestamp = *timestamp;
        return AVERROR(EAGAIN);

    case 3: /* Fragment other than first */
        if (!data->fragment) {
            av_log(ctx, AV_LOG_WARNING,
                   "Received packet without a start fragment; dropping.\n");
            return AVERROR(EAGAIN);
        }
        if (nr_frames != data->nr_frames ||
            data->timestamp != *timestamp) {
            ffio_free_dyn_buf(&data->fragment);
            av_log(ctx, AV_LOG_ERROR, "Invalid packet received\n");
            return AVERROR_INVALIDDATA;
        }

        avio_write(data->fragment, buf, len);
        data->last_frame++;
    }

    if (!(flags & RTP_FLAG_MARKER))
        return AVERROR(EAGAIN);

    if (data->last_frame != data->nr_frames) {
        ffio_free_dyn_buf(&data->fragment);
        av_log(ctx, AV_LOG_ERROR, "Missed %d packets\n",
               data->nr_frames - data->last_frame);
        return AVERROR_INVALIDDATA;
    }

    err = ff_rtp_finalize_packet(pkt, &data->fragment, st->index);
    if (err < 0) {
        av_log(ctx, AV_LOG_ERROR,
               "Error occurred when getting fragment buffer.\n");
        return err;
    }

    return 0;
}