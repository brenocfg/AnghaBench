#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  pb; } ;
struct TYPE_8__ {scalar_t__ stream_index; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int NC_VIDEO_FLAG ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 int avio_r8 (int /*<<< orphan*/ ) ; 
 int avio_rl16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nc_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int size;
    int ret;

    uint32_t state=-1;
    while (state != NC_VIDEO_FLAG) {
        if (avio_feof(s->pb))
            return AVERROR(EIO);
        state = (state<<8) + avio_r8(s->pb);
    }

    avio_r8(s->pb);
    size = avio_rl16(s->pb);
    avio_skip(s->pb, 9);

    if (size == 0) {
        av_log(s, AV_LOG_DEBUG, "Next packet size is zero\n");
        return AVERROR(EAGAIN);
    }

    ret = av_get_packet(s->pb, pkt, size);
    if (ret != size) {
        if (ret > 0) av_packet_unref(pkt);
        return AVERROR(EIO);
    }

    pkt->stream_index = 0;
    return size;
}