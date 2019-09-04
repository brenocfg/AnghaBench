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
struct TYPE_7__ {int nb_items; } ;
struct TYPE_6__ {scalar_t__ index_entry; } ;
typedef  TYPE_1__ MOVFragmentStreamInfo ;
typedef  TYPE_2__ MOVFragmentIndex ;

/* Variables and functions */
 TYPE_1__* get_frag_stream_info (TYPE_2__*,int,int) ; 

__attribute__((used)) static void fix_frag_index_entries(MOVFragmentIndex *frag_index, int index,
                                   int id, int entries)
{
    int i;
    MOVFragmentStreamInfo * frag_stream_info;

    if (index < 0)
        return;
    for (i = index; i < frag_index->nb_items; i++) {
        frag_stream_info = get_frag_stream_info(frag_index, i, id);
        if (frag_stream_info && frag_stream_info->index_entry >= 0)
            frag_stream_info->index_entry += entries;
    }
}