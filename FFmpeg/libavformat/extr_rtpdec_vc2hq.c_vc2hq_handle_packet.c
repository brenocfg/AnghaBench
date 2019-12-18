#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {scalar_t__ timestamp; scalar_t__ seen_sequence_header; scalar_t__ frame_size; scalar_t__ buf; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  DIRAC_PCODE_END_SEQ 130 
#define  DIRAC_PCODE_SEQ_HEADER 129 
#define  DIRAC_RTP_PCODE_HQ_PIC_FRAGMENT 128 
 int RTP_VC2HQ_PL_HEADER_SIZE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (scalar_t__*) ; 
 int vc2hq_handle_frame_fragment (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int const*,int,int) ; 
 int vc2hq_handle_sequence_header (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const*,int) ; 
 int vc2hq_mark_end_of_sequence (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vc2hq_handle_packet(AVFormatContext *ctx, PayloadContext *pl_ctx,
                               AVStream *st, AVPacket *pkt, uint32_t *timestamp,
                               const uint8_t *buf, int len, uint16_t seq,
                               int flags)
{
    uint8_t parse_code = 0;
    int res = 0;

    if (pl_ctx->buf && pl_ctx->timestamp != *timestamp) {
        av_log(ctx, AV_LOG_WARNING, "Dropping buffered RTP/VC2hq packet fragments - non-continuous timestamps\n");
        ffio_free_dyn_buf(&pl_ctx->buf);
        pl_ctx->frame_size = 0;
    }

    /* sanity check for size of input packet: needed header data as minimum */
    if (len < RTP_VC2HQ_PL_HEADER_SIZE) {
        av_log(ctx, AV_LOG_ERROR, "Too short RTP/VC2hq packet, got %d bytes\n", len);
        return AVERROR_INVALIDDATA;
    }

    parse_code = buf[3];

    /* wait for next sequence header? */
    if (pl_ctx->seen_sequence_header || parse_code == DIRAC_PCODE_SEQ_HEADER) {
        switch(parse_code) {
        /* sequence header */
        case DIRAC_PCODE_SEQ_HEADER:
            res = vc2hq_handle_sequence_header(pl_ctx, st, pkt, buf + RTP_VC2HQ_PL_HEADER_SIZE, len - RTP_VC2HQ_PL_HEADER_SIZE);
            break;
        /* end of sequence */
        case DIRAC_PCODE_END_SEQ:
            res = vc2hq_mark_end_of_sequence(pl_ctx, st, pkt);
            break;
        /* HQ picture fragment */
        case DIRAC_RTP_PCODE_HQ_PIC_FRAGMENT:
            res = vc2hq_handle_frame_fragment(ctx, pl_ctx, st, pkt, timestamp, buf, len, flags);
            break;
        }
    }

    return res;
}