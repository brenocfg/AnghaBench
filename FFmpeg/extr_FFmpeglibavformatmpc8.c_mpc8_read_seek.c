#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {int /*<<< orphan*/  pb; TYPE_2__** streams; } ;
struct TYPE_9__ {TYPE_1__* index_entries; } ;
struct TYPE_8__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  pos; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int av_index_search_timestamp (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_update_cur_dts (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc8_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    AVStream *st = s->streams[stream_index];
    int index = av_index_search_timestamp(st, timestamp, flags);

    if(index < 0) return -1;
    if (avio_seek(s->pb, st->index_entries[index].pos, SEEK_SET) < 0)
        return -1;
    ff_update_cur_dts(s, st, st->index_entries[index].timestamp);
    return 0;
}