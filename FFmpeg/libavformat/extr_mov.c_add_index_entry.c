#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_7__ {int pos; int timestamp; int min_distance; int size; int flags; } ;
struct TYPE_6__ {int nb_index_entries; size_t const index_entries_allocated_size; TYPE_2__* index_entries; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVIndexEntry ;

/* Variables and functions */
 size_t const FFMAX (size_t const,int) ; 
 int UINT_MAX ; 
 TYPE_2__* av_fast_realloc (TYPE_2__*,int*,size_t const) ; 

__attribute__((used)) static int64_t add_index_entry(AVStream *st, int64_t pos, int64_t timestamp,
                               int size, int distance, int flags)
{
    AVIndexEntry *entries, *ie;
    int64_t index = -1;
    const size_t min_size_needed = (st->nb_index_entries + 1) * sizeof(AVIndexEntry);

    // Double the allocation each time, to lower memory fragmentation.
    // Another difference from ff_add_index_entry function.
    const size_t requested_size =
        min_size_needed > st->index_entries_allocated_size ?
        FFMAX(min_size_needed, 2 * st->index_entries_allocated_size) :
        min_size_needed;

    if((unsigned)st->nb_index_entries + 1 >= UINT_MAX / sizeof(AVIndexEntry))
        return -1;

    entries = av_fast_realloc(st->index_entries,
                              &st->index_entries_allocated_size,
                              requested_size);
    if(!entries)
        return -1;

    st->index_entries= entries;

    index= st->nb_index_entries++;
    ie= &entries[index];

    ie->pos = pos;
    ie->timestamp = timestamp;
    ie->min_distance= distance;
    ie->size= size;
    ie->flags = flags;
    return index;
}