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
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ pts; int /*<<< orphan*/  remaining_size; } ;
typedef  TYPE_1__ VocDecContext ;
struct TYPE_11__ {int nb_streams; int /*<<< orphan*/  pb; TYPE_2__** streams; TYPE_1__* priv_data; } ;
struct TYPE_10__ {scalar_t__ timestamp; int /*<<< orphan*/  size; int /*<<< orphan*/  pos; } ;
struct TYPE_9__ {int nb_index_entries; TYPE_3__* index_entries; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVIndexEntry ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_index_search_timestamp (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int voc_read_seek(AVFormatContext *s, int stream_index,
                         int64_t timestamp, int flags)
{
    VocDecContext *voc = s->priv_data;
    AVStream *st;
    int index;

    if (s->nb_streams < 1) {
        av_log(s, AV_LOG_ERROR, "cannot seek while no stream was found yet\n");
        return AVERROR(EINVAL);
    }

    st = s->streams[stream_index];
    index = av_index_search_timestamp(st, timestamp, flags);

    if (index >= 0 && index < st->nb_index_entries - 1) {
        AVIndexEntry *e = &st->index_entries[index];
        avio_seek(s->pb, e->pos, SEEK_SET);
        voc->pts = e->timestamp;
        voc->remaining_size = e->size;
        return 0;
    } else if (st->nb_index_entries && st->index_entries[0].timestamp <= timestamp) {
        AVIndexEntry *e = &st->index_entries[st->nb_index_entries - 1];
        // prepare context for seek_frame_generic()
        voc->pts = e->timestamp;
        voc->remaining_size = e->size;
    }
    return -1;
}