#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {int nb_index_entries; TYPE_1__* index_entries; } ;
struct TYPE_10__ {scalar_t__ is_simple_index; } ;
struct TYPE_9__ {TYPE_6__** streams; int /*<<< orphan*/  pb; TYPE_3__* priv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASFContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_index_search_timestamp (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_seek_frame_binary (TYPE_2__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_packet_state (TYPE_2__*) ; 

__attribute__((used)) static int asf_read_seek(AVFormatContext *s, int stream_index,
                         int64_t timestamp, int flags)
{
    ASFContext *asf = s->priv_data;
    int idx, ret;

    if (s->streams[stream_index]->nb_index_entries && asf->is_simple_index) {
        idx = av_index_search_timestamp(s->streams[stream_index], timestamp, flags);
        if (idx < 0 || idx >= s->streams[stream_index]->nb_index_entries)
            return AVERROR_INVALIDDATA;
        avio_seek(s->pb, s->streams[stream_index]->index_entries[idx].pos, SEEK_SET);
    } else {
        if ((ret = ff_seek_frame_binary(s, stream_index, timestamp, flags)) < 0)
            return ret;
    }

    reset_packet_state(s);

    return 0;
}