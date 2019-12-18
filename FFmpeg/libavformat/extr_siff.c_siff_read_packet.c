#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_10__ {int data; int stream_index; int duration; int size; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {scalar_t__ cur_frame; scalar_t__ frames; int curstrm; unsigned int pktsize; int flags; int gmcsize; int gmc; int sndsize; int block_align; scalar_t__ has_video; } ;
typedef  TYPE_1__ SIFFContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_WL16 (int,int) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int VB_HAS_AUDIO ; 
 int VB_HAS_GMC ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ av_new_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 unsigned int avio_read (int /*<<< orphan*/ ,int,unsigned int) ; 
 int avio_rl16 (int /*<<< orphan*/ ) ; 
 void* avio_rl32 (int /*<<< orphan*/ ) ; 
 unsigned int ffio_limit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int,int,int) ; 

__attribute__((used)) static int siff_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    SIFFContext *c = s->priv_data;

    if (c->has_video) {
        unsigned int size;
        if (c->cur_frame >= c->frames)
            return AVERROR_EOF;
        if (c->curstrm == -1) {
            c->pktsize = avio_rl32(s->pb) - 4;
            c->flags   = avio_rl16(s->pb);
            c->gmcsize = (c->flags & VB_HAS_GMC) ? 4 : 0;
            if (c->gmcsize)
                avio_read(s->pb, c->gmc, c->gmcsize);
            c->sndsize = (c->flags & VB_HAS_AUDIO) ? avio_rl32(s->pb) : 0;
            c->curstrm = !!(c->flags & VB_HAS_AUDIO);
        }

        if (!c->curstrm) {
            if (c->pktsize < 2LL + c->sndsize + c->gmcsize)
                return AVERROR_INVALIDDATA;

            size = c->pktsize - c->sndsize - c->gmcsize - 2;
            size = ffio_limit(s->pb, size);
            if (av_new_packet(pkt, size + c->gmcsize + 2) < 0)
                return AVERROR(ENOMEM);
            AV_WL16(pkt->data, c->flags);
            if (c->gmcsize)
                memcpy(pkt->data + 2, c->gmc, c->gmcsize);
            if (avio_read(s->pb, pkt->data + 2 + c->gmcsize, size) != size) {
                av_packet_unref(pkt);
                return AVERROR_INVALIDDATA;
            }
            pkt->stream_index = 0;
            c->curstrm        = -1;
        } else {
            int pktsize = av_get_packet(s->pb, pkt, c->sndsize - 4);
            if (pktsize < 0)
                return AVERROR(EIO);
            pkt->stream_index = 1;
            pkt->duration     = pktsize;
            c->curstrm        = 0;
        }
        if (!c->cur_frame || c->curstrm)
            pkt->flags |= AV_PKT_FLAG_KEY;
        if (c->curstrm == -1)
            c->cur_frame++;
    } else {
        int pktsize = av_get_packet(s->pb, pkt, c->block_align);
        if (!pktsize)
            return AVERROR_EOF;
        if (pktsize <= 0)
            return AVERROR(EIO);
        pkt->duration = pktsize;
    }
    return pkt->size;
}