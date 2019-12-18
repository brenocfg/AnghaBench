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
typedef  scalar_t__ int64_t ;
struct TYPE_14__ {int nb_streams; TYPE_1__** streams; int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_13__ {scalar_t__ pos; int size; int /*<<< orphan*/  timestamp; } ;
struct TYPE_12__ {int stream_index; int /*<<< orphan*/  pts; } ;
struct TYPE_11__ {size_t* index_pos; } ;
struct TYPE_10__ {size_t nb_index_entries; TYPE_4__* index_entries; } ;
typedef  TYPE_2__ Rl2DemuxContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVIndexEntry ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rl2_read_packet(AVFormatContext *s,
                            AVPacket *pkt)
{
    Rl2DemuxContext *rl2 = s->priv_data;
    AVIOContext *pb = s->pb;
    AVIndexEntry *sample = NULL;
    int i;
    int ret = 0;
    int stream_id = -1;
    int64_t pos = INT64_MAX;

    /** check if there is a valid video or audio entry that can be used */
    for(i=0; i<s->nb_streams; i++){
        if(rl2->index_pos[i] < s->streams[i]->nb_index_entries
              && s->streams[i]->index_entries[ rl2->index_pos[i] ].pos < pos){
            sample = &s->streams[i]->index_entries[ rl2->index_pos[i] ];
            pos= sample->pos;
            stream_id= i;
        }
    }

    if(stream_id == -1)
        return AVERROR_EOF;

    ++rl2->index_pos[stream_id];

    /** position the stream (will probably be there anyway) */
    avio_seek(pb, sample->pos, SEEK_SET);

    /** fill the packet */
    ret = av_get_packet(pb, pkt, sample->size);
    if(ret != sample->size){
        av_packet_unref(pkt);
        return AVERROR(EIO);
    }

    pkt->stream_index = stream_id;
    pkt->pts = sample->timestamp;

    return ret;
}