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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_7__ {int stream_index; int /*<<< orphan*/  pts; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ read_part_of_packet (TYPE_2__*,int /*<<< orphan*/ *,int*,int*,int) ; 

__attribute__((used)) static int pva_read_packet(AVFormatContext *s, AVPacket *pkt) {
    AVIOContext *pb = s->pb;
    int64_t pva_pts;
    int ret, length, streamid;

    if (read_part_of_packet(s, &pva_pts, &length, &streamid, 1) < 0 ||
       (ret = av_get_packet(pb, pkt, length)) <= 0)
        return AVERROR(EIO);

    pkt->stream_index = streamid - 1;
    pkt->pts = pva_pts;

    return ret;
}