#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {int nb_streams; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  time_base; TYPE_1__* index_entries; } ;
struct TYPE_8__ {int* index_pos; } ;
struct TYPE_7__ {int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_2__ Rl2DemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVSEEK_FLAG_BACKWARD ; 
 int av_index_search_timestamp (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rl2_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    AVStream *st = s->streams[stream_index];
    Rl2DemuxContext *rl2 = s->priv_data;
    int i;
    int index = av_index_search_timestamp(st, timestamp, flags);
    if(index < 0)
        return -1;

    rl2->index_pos[stream_index] = index;
    timestamp = st->index_entries[index].timestamp;

    for(i=0; i < s->nb_streams; i++){
        AVStream *st2 = s->streams[i];
        index = av_index_search_timestamp(st2,
                    av_rescale_q(timestamp, st->time_base, st2->time_base),
                    flags | AVSEEK_FLAG_BACKWARD);

        if(index < 0)
            index = 0;

        rl2->index_pos[i] = index;
    }

    return 0;
}