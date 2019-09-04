#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {int nb_streams; int /*<<< orphan*/  pb; TYPE_2__** streams; } ;
struct TYPE_7__ {int nb_index_entries; TYPE_1__* index_entries; } ;
struct TYPE_6__ {scalar_t__ pos; int size; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 unsigned int avio_r8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_rl16 (int /*<<< orphan*/ ) ; 
 unsigned int avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 
 int check_stream_max_drift (TYPE_3__*) ; 
 int get_stream_idx (unsigned int*) ; 

__attribute__((used)) static int guess_ni_flag(AVFormatContext *s)
{
    int i;
    int64_t last_start = 0;
    int64_t first_end  = INT64_MAX;
    int64_t oldpos     = avio_tell(s->pb);

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        int n        = st->nb_index_entries;
        unsigned int size;

        if (n <= 0)
            continue;

        if (n >= 2) {
            int64_t pos = st->index_entries[0].pos;
            unsigned tag[2];
            avio_seek(s->pb, pos, SEEK_SET);
            tag[0] = avio_r8(s->pb);
            tag[1] = avio_r8(s->pb);
            avio_rl16(s->pb);
            size = avio_rl32(s->pb);
            if (get_stream_idx(tag) == i && pos + size > st->index_entries[1].pos)
                last_start = INT64_MAX;
            if (get_stream_idx(tag) == i && size == st->index_entries[0].size + 8)
                last_start = INT64_MAX;
        }

        if (st->index_entries[0].pos > last_start)
            last_start = st->index_entries[0].pos;
        if (st->index_entries[n - 1].pos < first_end)
            first_end = st->index_entries[n - 1].pos;
    }
    avio_seek(s->pb, oldpos, SEEK_SET);

    if (last_start > first_end)
        return 1;

    return check_stream_max_drift(s);
}