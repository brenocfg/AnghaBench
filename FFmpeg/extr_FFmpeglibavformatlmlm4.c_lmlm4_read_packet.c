#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_7__ {int stream_index; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EIO ; 
#define  LMLM4_B_FRAME 131 
 unsigned int LMLM4_INVALID ; 
#define  LMLM4_I_FRAME 130 
 unsigned int LMLM4_MAX_PACKET_SIZE ; 
#define  LMLM4_MPEG1L2 129 
#define  LMLM4_P_FRAME 128 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 unsigned int avio_rb16 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int lmlm4_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVIOContext *pb = s->pb;
    int ret;
    unsigned int frame_type, packet_size, padding, frame_size;

    avio_rb16(pb);                       /* channel number */
    frame_type  = avio_rb16(pb);
    packet_size = avio_rb32(pb);
    padding     = -packet_size & 511;
    frame_size  = packet_size - 8;

    if (frame_type > LMLM4_MPEG1L2 || frame_type == LMLM4_INVALID) {
        av_log(s, AV_LOG_ERROR, "invalid or unsupported frame_type\n");
        return AVERROR(EIO);
    }
    if (packet_size > LMLM4_MAX_PACKET_SIZE || packet_size<=8) {
        av_log(s, AV_LOG_ERROR, "packet size %d is invalid\n", packet_size);
        return AVERROR(EIO);
    }

    if ((ret = av_get_packet(pb, pkt, frame_size)) <= 0)
        return AVERROR(EIO);

    avio_skip(pb, padding);

    switch (frame_type) {
    case LMLM4_I_FRAME:
        pkt->flags = AV_PKT_FLAG_KEY;
    case LMLM4_P_FRAME:
    case LMLM4_B_FRAME:
        pkt->stream_index = 0;
        break;
    case LMLM4_MPEG1L2:
        pkt->stream_index = 1;
        break;
    }

    return ret;
}