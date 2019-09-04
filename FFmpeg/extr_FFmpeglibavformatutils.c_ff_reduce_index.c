#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int max_index_size; TYPE_1__** streams; } ;
struct TYPE_4__ {int nb_index_entries; int /*<<< orphan*/ * index_entries; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIndexEntry ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */

void ff_reduce_index(AVFormatContext *s, int stream_index)
{
    AVStream *st             = s->streams[stream_index];
    unsigned int max_entries = s->max_index_size / sizeof(AVIndexEntry);

    if ((unsigned) st->nb_index_entries >= max_entries) {
        int i;
        for (i = 0; 2 * i < st->nb_index_entries; i++)
            st->index_entries[i] = st->index_entries[2 * i];
        st->nb_index_entries = i;
    }
}