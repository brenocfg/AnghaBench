#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  pb; TYPE_4__** streams; TYPE_3__* priv_data; } ;
struct TYPE_11__ {TYPE_1__* index_entries; TYPE_2__* priv_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
struct TYPE_9__ {int /*<<< orphan*/  frame_offset; } ;
struct TYPE_8__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  pos; } ;
typedef  TYPE_2__ NSVStream ;
typedef  TYPE_3__ NSVContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  NSV_UNSYNC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_index_search_timestamp (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsv_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    NSVContext *nsv = s->priv_data;
    AVStream *st = s->streams[stream_index];
    NSVStream *nst = st->priv_data;
    int index;

    index = av_index_search_timestamp(st, timestamp, flags);
    if(index < 0)
        return -1;

    if (avio_seek(s->pb, st->index_entries[index].pos, SEEK_SET) < 0)
        return -1;

    nst->frame_offset = st->index_entries[index].timestamp;
    nsv->state = NSV_UNSYNC;
    return 0;
}