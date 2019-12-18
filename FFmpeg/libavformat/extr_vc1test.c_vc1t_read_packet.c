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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {TYPE_2__** streams; int /*<<< orphan*/ * pb; } ;
struct TYPE_10__ {int pos; int size; int /*<<< orphan*/  flags; int /*<<< orphan*/  pts; } ;
struct TYPE_8__ {int den; } ;
struct TYPE_9__ {TYPE_1__ time_base; } ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ av_get_packet (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rl24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vc1t_read_packet(AVFormatContext *s,
                           AVPacket *pkt)
{
    AVIOContext *pb = s->pb;
    int frame_size;
    int keyframe = 0;
    uint32_t pts;

    if(avio_feof(pb))
        return AVERROR(EIO);

    frame_size = avio_rl24(pb);
    if(avio_r8(pb) & 0x80)
        keyframe = 1;
    pts = avio_rl32(pb);
    if(av_get_packet(pb, pkt, frame_size) < 0)
        return AVERROR(EIO);
    if(s->streams[0]->time_base.den == 1000)
        pkt->pts = pts;
    pkt->flags |= keyframe ? AV_PKT_FLAG_KEY : 0;
    pkt->pos -= 8;

    return pkt->size;
}