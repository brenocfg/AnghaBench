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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {TYPE_2__* priv_data; TYPE_3__** streams; } ;
struct TYPE_10__ {int nb_index_entries; TYPE_1__* index_entries; } ;
struct TYPE_9__ {scalar_t__ curframe; scalar_t__ fcount; scalar_t__ frames_noted; } ;
struct TYPE_8__ {scalar_t__ timestamp; scalar_t__ pos; } ;
typedef  TYPE_2__ MPCContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ DELAY_FRAMES ; 
 int /*<<< orphan*/  FFMAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int av_index_search_timestamp (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int av_read_frame (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpc_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    AVStream *st = s->streams[stream_index];
    MPCContext *c = s->priv_data;
    AVPacket pkt1, *pkt = &pkt1;
    int ret;
    int index = av_index_search_timestamp(st, FFMAX(timestamp - DELAY_FRAMES, 0), flags);
    uint32_t lastframe;

    /* if found, seek there */
    if (index >= 0 && st->index_entries[st->nb_index_entries-1].timestamp >= timestamp - DELAY_FRAMES){
        c->curframe = st->index_entries[index].pos;
        return 0;
    }
    /* if timestamp is out of bounds, return error */
    if(timestamp < 0 || timestamp >= c->fcount)
        return -1;
    timestamp -= DELAY_FRAMES;
    /* seek to the furthest known position and read packets until
       we reach desired position */
    lastframe = c->curframe;
    if(c->frames_noted) c->curframe = c->frames_noted - 1;
    while(c->curframe < timestamp){
        ret = av_read_frame(s, pkt);
        if (ret < 0){
            c->curframe = lastframe;
            return ret;
        }
        av_packet_unref(pkt);
    }
    return 0;
}