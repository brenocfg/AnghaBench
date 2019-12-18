#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  pb; int /*<<< orphan*/ * streams; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int* data; int pts; int size; scalar_t__ stream_index; } ;
struct TYPE_10__ {int curframe; int fcount; int lastframe; int curbits; int frames_noted; TYPE_1__* frames; } ;
struct TYPE_9__ {int pos; int skip; int size; } ;
typedef  TYPE_2__ MPCContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_add_index_entry (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_new_packet (TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int avio_read (int /*<<< orphan*/ ,int*,int) ; 
 int avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    MPCContext *c = s->priv_data;
    int ret, size, size2, curbits, cur = c->curframe;
    unsigned tmp;
    int64_t pos;

    if (c->curframe >= c->fcount && c->fcount)
        return AVERROR_EOF;

    if(c->curframe != c->lastframe + 1){
        avio_seek(s->pb, c->frames[c->curframe].pos, SEEK_SET);
        c->curbits = c->frames[c->curframe].skip;
    }
    c->lastframe = c->curframe;
    c->curframe++;
    curbits = c->curbits;
    pos = avio_tell(s->pb);
    tmp = avio_rl32(s->pb);
    if(curbits <= 12){
        size2 = (tmp >> (12 - curbits)) & 0xFFFFF;
    }else{
        size2 = (tmp << (curbits - 12) | avio_rl32(s->pb) >> (44 - curbits)) & 0xFFFFF;
    }
    curbits += 20;
    avio_seek(s->pb, pos, SEEK_SET);

    size = ((size2 + curbits + 31) & ~31) >> 3;
    if(cur == c->frames_noted && c->fcount){
        c->frames[cur].pos = pos;
        c->frames[cur].size = size;
        c->frames[cur].skip = curbits - 20;
        av_add_index_entry(s->streams[0], cur, cur, size, 0, AVINDEX_KEYFRAME);
        c->frames_noted++;
    }
    c->curbits = (curbits + size2) & 0x1F;

    if ((ret = av_new_packet(pkt, size + 4)) < 0)
        return ret;

    pkt->data[0] = curbits;
    pkt->data[1] = (c->curframe > c->fcount) && c->fcount;
    pkt->data[2] = 0;
    pkt->data[3] = 0;

    pkt->stream_index = 0;
    pkt->pts = cur;
    ret = avio_read(s->pb, pkt->data + 4, size);
    if(c->curbits)
        avio_seek(s->pb, -4, SEEK_CUR);
    if(ret < size){
        av_packet_unref(pkt);
        return ret < 0 ? ret : AVERROR(EIO);
    }
    pkt->size = ret + 4;

    return 0;
}