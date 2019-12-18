#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  dts; } ;
struct TYPE_12__ {size_t nb_index_entries; TYPE_1__* index_entries; } ;
struct TYPE_11__ {size_t currentframe; size_t totalframes; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  last_frame_size; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_2__ TTAContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tta_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    TTAContext *c = s->priv_data;
    AVStream *st = s->streams[0];
    int size, ret;

    // FIXME!
    if (c->currentframe >= c->totalframes)
        return AVERROR_EOF;

    if (st->nb_index_entries < c->totalframes) {
        av_log(s, AV_LOG_ERROR, "Index entry disappeared\n");
        return AVERROR_INVALIDDATA;
    }

    size = st->index_entries[c->currentframe].size;

    ret = av_get_packet(s->pb, pkt, size);
    pkt->dts = st->index_entries[c->currentframe++].timestamp;
    pkt->duration = c->currentframe == c->totalframes ? c->last_frame_size :
                                                        c->frame_size;
    return ret;
}