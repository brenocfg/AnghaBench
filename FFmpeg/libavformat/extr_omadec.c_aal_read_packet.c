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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {TYPE_2__** streams; int /*<<< orphan*/  pb; } ;
struct TYPE_10__ {int duration; int pts; int /*<<< orphan*/  pos; scalar_t__ stream_index; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {scalar_t__ codec_id; } ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_ATRAC3AL ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 unsigned int MKBETAG (int /*<<< orphan*/ ,char,char,char) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 int avio_rb16 (int /*<<< orphan*/ ) ; 
 unsigned int avio_rb24 (int /*<<< orphan*/ ) ; 
 int avio_rb32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aal_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int64_t pos = avio_tell(s->pb);
    int ret, pts;
    int packet_size;
    unsigned tag;

    if (avio_feof(s->pb))
        return AVERROR_EOF;

    tag = avio_rb24(s->pb);
    if (tag == 0)
        return AVERROR_EOF;
    else if (tag != MKBETAG(0,'B','L','K'))
        return AVERROR_INVALIDDATA;

    avio_skip(s->pb, 1);
    packet_size = avio_rb16(s->pb);
    avio_skip(s->pb, 2);
    pts = avio_rb32(s->pb);
    avio_skip(s->pb, 12);
    ret = av_get_packet(s->pb, pkt, packet_size);
    if (ret < packet_size)
        pkt->flags |= AV_PKT_FLAG_CORRUPT;

    if (ret < 0)
        return ret;
    if (!ret)
        return AVERROR_EOF;

    pkt->stream_index = 0;
    pkt->pos = pos;
    if (s->streams[0]->codecpar->codec_id == AV_CODEC_ID_ATRAC3AL) {
        pkt->duration = 1024;
        pkt->pts = pts * 1024LL;
    } else {
        pkt->duration = 2048;
        pkt->pts = pts * 2048LL;
    }

    return ret;
}