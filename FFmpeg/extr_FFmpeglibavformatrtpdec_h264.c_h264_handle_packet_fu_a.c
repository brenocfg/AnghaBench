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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  PayloadContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int ff_h264_handle_frag_packet (int /*<<< orphan*/ *,int const*,int,int,int*,int) ; 

__attribute__((used)) static int h264_handle_packet_fu_a(AVFormatContext *ctx, PayloadContext *data, AVPacket *pkt,
                                   const uint8_t *buf, int len,
                                   int *nal_counters, int nal_mask)
{
    uint8_t fu_indicator, fu_header, start_bit, nal_type, nal;

    if (len < 3) {
        av_log(ctx, AV_LOG_ERROR, "Too short data for FU-A H.264 RTP packet\n");
        return AVERROR_INVALIDDATA;
    }

    fu_indicator = buf[0];
    fu_header    = buf[1];
    start_bit    = fu_header >> 7;
    nal_type     = fu_header & 0x1f;
    nal          = fu_indicator & 0xe0 | nal_type;

    // skip the fu_indicator and fu_header
    buf += 2;
    len -= 2;

    if (start_bit && nal_counters)
        nal_counters[nal_type & nal_mask]++;
    return ff_h264_handle_frag_packet(pkt, buf, len, start_bit, &nal, 1);
}