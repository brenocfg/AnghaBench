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
struct TYPE_11__ {TYPE_2__** streams; int /*<<< orphan*/  pb; } ;
struct TYPE_10__ {scalar_t__ stream_index; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int /*<<< orphan*/  block_align; } ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aea_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret = av_get_packet(s->pb, pkt, s->streams[0]->codecpar->block_align);

    pkt->stream_index = 0;
    if (ret <= 0)
        return AVERROR(EIO);

    return ret;
}