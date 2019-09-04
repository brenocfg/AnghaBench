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
typedef  void* int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  pb; } ;
struct TYPE_7__ {int size; scalar_t__ data; void* dts; void* pts; void* pos; int /*<<< orphan*/  flags; scalar_t__ stream_index; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 size_t AV_RB16 (scalar_t__) ; 
 scalar_t__ SUP_PGS_MAGIC ; 
 int av_append_packet (int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 scalar_t__ avio_rb16 (int /*<<< orphan*/ ) ; 
 void* avio_rb32 (int /*<<< orphan*/ ) ; 
 void* avio_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sup_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int64_t pts, dts, pos;
    int ret;

    pos = avio_tell(s->pb);

    if (avio_rb16(s->pb) != SUP_PGS_MAGIC)
        return avio_feof(s->pb) ? AVERROR_EOF : AVERROR_INVALIDDATA;

    pts = avio_rb32(s->pb);
    dts = avio_rb32(s->pb);

    if ((ret = av_get_packet(s->pb, pkt, 3)) < 0)
        return ret;

    pkt->stream_index = 0;
    pkt->flags |= AV_PKT_FLAG_KEY;
    pkt->pos = pos;
    pkt->pts = pts;
    // Many files have DTS set to 0 for all packets, so assume 0 means unset.
    pkt->dts = dts ? dts : AV_NOPTS_VALUE;

    if (pkt->size >= 3) {
        // The full packet size is stored as part of the packet.
        size_t len = AV_RB16(pkt->data + 1);

        if ((ret = av_append_packet(s->pb, pkt, len)) < 0)
            return ret;
    }

    return 0;
}