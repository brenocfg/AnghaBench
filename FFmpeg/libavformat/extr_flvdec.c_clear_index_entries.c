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
struct TYPE_8__ {int nb_streams; TYPE_2__** streams; } ;
struct TYPE_7__ {int nb_index_entries; TYPE_1__* index_entries; } ;
struct TYPE_6__ {scalar_t__ pos; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void clear_index_entries(AVFormatContext *s, int64_t pos)
{
    int i, j, out;
    av_log(s, AV_LOG_WARNING,
           "Found invalid index entries, clearing the index.\n");
    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        /* Remove all index entries that point to >= pos */
        out = 0;
        for (j = 0; j < st->nb_index_entries; j++)
            if (st->index_entries[j].pos < pos)
                st->index_entries[out++] = st->index_entries[j];
        st->nb_index_entries = out;
    }
}