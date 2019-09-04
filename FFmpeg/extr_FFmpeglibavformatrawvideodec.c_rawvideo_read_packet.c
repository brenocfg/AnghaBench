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
struct TYPE_7__ {int packet_size; int /*<<< orphan*/  pb; } ;
struct TYPE_6__ {int pts; int dts; int pos; scalar_t__ stream_index; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int av_get_packet (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int rawvideo_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret;

    ret = av_get_packet(s->pb, pkt, s->packet_size);
    pkt->pts = pkt->dts = pkt->pos / s->packet_size;

    pkt->stream_index = 0;
    if (ret < 0)
        return ret;
    return 0;
}