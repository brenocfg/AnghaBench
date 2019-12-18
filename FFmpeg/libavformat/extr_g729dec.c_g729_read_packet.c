#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  pb; TYPE_2__** streams; } ;
struct TYPE_10__ {int dts; int pts; int pos; int duration; scalar_t__ stream_index; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int block_align; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int av_get_packet (int /*<<< orphan*/ ,TYPE_3__*,int) ; 

__attribute__((used)) static int g729_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVStream *st = s->streams[0];
    int ret = av_get_packet(s->pb, pkt, st->codecpar->block_align);
    if (ret < 0)
        return ret;

    pkt->stream_index = 0;
    pkt->dts = pkt->pts = pkt->pos / st->codecpar->block_align;
    pkt->duration = 1;

    return 0;
}