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
typedef  int uint8_t ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int* buf; scalar_t__ max_payload_size; int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FFMIN (scalar_t__,int) ; 
 size_t RTP_H261_HEADER_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_rtp_send_data (TYPE_2__*,int*,size_t,int) ; 
 int* find_resync_marker_reverse (int const*,int const*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

void ff_rtp_send_h261(AVFormatContext *ctx, const uint8_t *frame_buf, int frame_size)
{
    int cur_frame_size;
    int last_packet_of_frame;
    RTPMuxContext *rtp_ctx = ctx->priv_data;

    /* use the default 90 KHz time stamp */
    rtp_ctx->timestamp = rtp_ctx->cur_timestamp;

    /* continue as long as not all frame data is processed */
    while (frame_size > 0) {
        /*
         * encode the H.261 payload header according to section 4.1 of RFC 4587:
         * (uses 4 bytes between RTP header and H.261 stream per packet)
         *
         *    0                   1                   2                   3
         *    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
         *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         *   |SBIT |EBIT |I|V| GOBN  |   MBAP  |  QUANT  |  HMVD   |  VMVD   |
         *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         *
         *      Start bit position (SBIT): 3 bits
         *      End bit position (EBIT): 3 bits
         *      INTRA-frame encoded data (I): 1 bit
         *      Motion Vector flag (V): 1 bit
         *      GOB number (GOBN): 4 bits
         *      Macroblock address predictor (MBAP): 5 bits
         *      Quantizer (QUANT): 5 bits
         *      Horizontal motion vector data (HMVD): 5 bits
         *      Vertical motion vector data (VMVD): 5 bits
         */
        rtp_ctx->buf[0] = 1; /* sbit=0, ebit=0, i=0, v=1 */
        rtp_ctx->buf[1] = 0; /* gobn=0, mbap=0 */
        rtp_ctx->buf[2] = 0; /* quant=0, hmvd=5 */
        rtp_ctx->buf[3] = 0; /* vmvd=0 */
        if (frame_size < 2 || frame_buf[0] != 0 || frame_buf[1] != 1) {
            /* A full, correct fix for this would be to make the H.261 encoder
             * support inserting extra GOB headers (triggered by setting e.g.
             * "-ps 1"), and including information about macroblock boundaries
             * (such as for h263_rfc2190). */
            av_log(ctx, AV_LOG_WARNING,
                   "RTP/H.261 packet not cut at a GOB boundary, not signaled correctly\n");
        }

        cur_frame_size = FFMIN(rtp_ctx->max_payload_size - RTP_H261_HEADER_SIZE, frame_size);

        /* look for a better place to split the frame into packets */
        if (cur_frame_size < frame_size) {
            const uint8_t *packet_end = find_resync_marker_reverse(frame_buf,
                                                                   frame_buf + cur_frame_size);
            cur_frame_size = packet_end - frame_buf;
        }

        /* calculate the "marker" bit for the RTP header */
        last_packet_of_frame = cur_frame_size == frame_size;

        /* complete and send RTP packet */
        memcpy(&rtp_ctx->buf[RTP_H261_HEADER_SIZE], frame_buf, cur_frame_size);
        ff_rtp_send_data(ctx, rtp_ctx->buf, RTP_H261_HEADER_SIZE + cur_frame_size, last_packet_of_frame);

        frame_buf  += cur_frame_size;
        frame_size -= cur_frame_size;
    }
}