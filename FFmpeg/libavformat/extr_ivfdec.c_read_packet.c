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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {int /*<<< orphan*/  pb; } ;
struct TYPE_6__ {int pos; int /*<<< orphan*/  pts; scalar_t__ stream_index; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int av_get_packet (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_rl64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret, size = avio_rl32(s->pb);
    int64_t   pts = avio_rl64(s->pb);

    ret = av_get_packet(s->pb, pkt, size);
    pkt->stream_index = 0;
    pkt->pts          = pts;
    pkt->pos         -= 12;

    return ret;
}