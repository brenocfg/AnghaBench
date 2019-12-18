#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {int /*<<< orphan*/  pb; } ;
struct TYPE_9__ {int stream_index; int /*<<< orphan*/  flags; scalar_t__ pos; scalar_t__ data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FIRST ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_1__*,unsigned int) ; 
 scalar_t__ av_new_packet (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_1__*,int) ; 
 int avio_read (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 void* avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  header ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sdr2_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int64_t pos;
    unsigned next;
    int flags, ret = 0, is_video;

    pos = avio_tell(s->pb);

    flags = avio_rl32(s->pb);
    avio_skip(s->pb, 4);

    next = avio_rl32(s->pb);
    if (next <= 52)
        return AVERROR_INVALIDDATA;

    avio_skip(s->pb, 6);
    is_video = avio_rl32(s->pb);
    avio_skip(s->pb, 30);

    if (pos == FIRST) {
        if (av_new_packet(pkt, next - 52 + 24) < 0)
            return AVERROR(ENOMEM);
        memcpy(pkt->data, header, 24);
        ret = avio_read(s->pb, pkt->data + 24, next - 52);
        if (ret < 0) {
            av_packet_unref(pkt);
            return ret;
        }
        av_shrink_packet(pkt, ret + 24);
    } else {
        ret = av_get_packet(s->pb, pkt, next - 52);
    }
    pkt->stream_index = !!is_video;
    pkt->pos = pos;
    if (flags & (1 << 12))
        pkt->flags |= AV_PKT_FLAG_KEY;

    return ret;
}