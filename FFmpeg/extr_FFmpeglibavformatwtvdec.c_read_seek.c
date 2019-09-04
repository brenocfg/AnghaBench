#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {scalar_t__ epoch; int nb_index_entries; scalar_t__ last_valid_pts; scalar_t__ pts; TYPE_6__* index_entries; int /*<<< orphan*/ * pb; } ;
typedef  TYPE_1__ WtvContext ;
struct TYPE_10__ {scalar_t__ timestamp; int /*<<< orphan*/  pos; } ;
struct TYPE_9__ {TYPE_2__** streams; TYPE_1__* priv_data; } ;
struct TYPE_8__ {scalar_t__ duration; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVSEEK_FLAG_BYTE ; 
 int AVSEEK_FLAG_FRAME ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SEEK_TO_PTS ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_index_search_timestamp (TYPE_6__*,int,scalar_t__,int) ; 
 scalar_t__ parse_chunks (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_seek(AVFormatContext *s, int stream_index,
                     int64_t ts, int flags)
{
    WtvContext *wtv = s->priv_data;
    AVIOContext *pb = wtv->pb;
    AVStream *st = s->streams[0];
    int64_t ts_relative;
    int i;

    if ((flags & AVSEEK_FLAG_FRAME) || (flags & AVSEEK_FLAG_BYTE))
        return AVERROR(ENOSYS);

    /* timestamp adjustment is required because wtv->pts values are absolute,
     * whereas AVIndexEntry->timestamp values are relative to epoch. */
    ts_relative = ts;
    if (wtv->epoch != AV_NOPTS_VALUE)
        ts_relative -= wtv->epoch;

    i = ff_index_search_timestamp(wtv->index_entries, wtv->nb_index_entries, ts_relative, flags);
    if (i < 0) {
        if (wtv->last_valid_pts == AV_NOPTS_VALUE || ts < wtv->last_valid_pts) {
            if (avio_seek(pb, 0, SEEK_SET) < 0)
                return -1;
        } else if (st->duration != AV_NOPTS_VALUE && ts_relative > st->duration && wtv->nb_index_entries) {
            if (avio_seek(pb, wtv->index_entries[wtv->nb_index_entries - 1].pos, SEEK_SET) < 0)
                return -1;
        }
        if (parse_chunks(s, SEEK_TO_PTS, ts, 0) < 0)
            return AVERROR(ERANGE);
        return 0;
    }
    if (avio_seek(pb, wtv->index_entries[i].pos, SEEK_SET) < 0)
        return -1;
    wtv->pts = wtv->index_entries[i].timestamp;
    if (wtv->epoch != AV_NOPTS_VALUE)
        wtv->pts += wtv->epoch;
    wtv->last_valid_pts = wtv->pts;
    return 0;
}