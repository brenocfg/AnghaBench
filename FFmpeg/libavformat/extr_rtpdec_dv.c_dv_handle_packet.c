#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {scalar_t__ timestamp; scalar_t__ buf; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int RTP_FLAG_MARKER ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int avio_open_dyn_buf (scalar_t__*) ; 
 int /*<<< orphan*/  avio_write (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int ff_rtp_finalize_packet (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (scalar_t__*) ; 

__attribute__((used)) static int dv_handle_packet(AVFormatContext *ctx, PayloadContext *rtp_dv_ctx,
                            AVStream *st, AVPacket *pkt, uint32_t *timestamp,
                            const uint8_t *buf, int len, uint16_t seq,
                            int flags)
{
    int res = 0;

    /* drop data of previous packets in case of non-continuous (lossy) packet stream */
    if (rtp_dv_ctx->buf && rtp_dv_ctx->timestamp != *timestamp) {
        ffio_free_dyn_buf(&rtp_dv_ctx->buf);
    }

    /* sanity check for size of input packet: 1 byte payload at least */
    if (len < 1) {
        av_log(ctx, AV_LOG_ERROR, "Too short RTP/DV packet, got %d bytes\n", len);
        return AVERROR_INVALIDDATA;
    }

    /* start frame buffering with new dynamic buffer */
    if (!rtp_dv_ctx->buf) {
        res = avio_open_dyn_buf(&rtp_dv_ctx->buf);
        if (res < 0)
            return res;
        /* update the timestamp in the frame packet with the one from the RTP packet */
        rtp_dv_ctx->timestamp = *timestamp;
    }

    /* write the fragment to the dyn. buffer */
    avio_write(rtp_dv_ctx->buf, buf, len);

    /* RTP marker bit means: last fragment of current frame was received;
       otherwise, an additional fragment is needed for the current frame */
    if (!(flags & RTP_FLAG_MARKER))
        return AVERROR(EAGAIN);

    /* close frame buffering and create resulting A/V packet */
    res = ff_rtp_finalize_packet(pkt, &rtp_dv_ctx->buf, st->index);
    if (res < 0)
        return res;

    return 0;
}