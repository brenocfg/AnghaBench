#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_13__ {size_t currentframe; size_t totalframes; int finalframeblocks; int blocksperframe; TYPE_1__* frames; } ;
struct TYPE_12__ {int /*<<< orphan*/  pb; TYPE_4__* priv_data; } ;
struct TYPE_11__ {scalar_t__ data; scalar_t__ size; scalar_t__ stream_index; int /*<<< orphan*/  pts; } ;
struct TYPE_10__ {scalar_t__ size; int skip; int /*<<< orphan*/  pts; int /*<<< orphan*/  pos; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ APEContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_WL32 (scalar_t__,int) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ av_new_packet (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 int avio_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ape_read_packet(AVFormatContext * s, AVPacket * pkt)
{
    int ret;
    int nblocks;
    APEContext *ape = s->priv_data;
    uint32_t extra_size = 8;

    if (avio_feof(s->pb))
        return AVERROR_EOF;
    if (ape->currentframe >= ape->totalframes)
        return AVERROR_EOF;

    if (avio_seek(s->pb, ape->frames[ape->currentframe].pos, SEEK_SET) < 0)
        return AVERROR(EIO);

    /* Calculate how many blocks there are in this frame */
    if (ape->currentframe == (ape->totalframes - 1))
        nblocks = ape->finalframeblocks;
    else
        nblocks = ape->blocksperframe;

    if (ape->frames[ape->currentframe].size <= 0 ||
        ape->frames[ape->currentframe].size > INT_MAX - extra_size) {
        av_log(s, AV_LOG_ERROR, "invalid packet size: %d\n",
               ape->frames[ape->currentframe].size);
        ape->currentframe++;
        return AVERROR(EIO);
    }

    if (av_new_packet(pkt,  ape->frames[ape->currentframe].size + extra_size) < 0)
        return AVERROR(ENOMEM);

    AV_WL32(pkt->data    , nblocks);
    AV_WL32(pkt->data + 4, ape->frames[ape->currentframe].skip);
    ret = avio_read(s->pb, pkt->data + extra_size, ape->frames[ape->currentframe].size);
    if (ret < 0) {
        av_packet_unref(pkt);
        return ret;
    }

    pkt->pts = ape->frames[ape->currentframe].pts;
    pkt->stream_index = 0;

    /* note: we need to modify the packet size here to handle the last
       packet */
    pkt->size = ret + extra_size;

    ape->currentframe++;

    return 0;
}