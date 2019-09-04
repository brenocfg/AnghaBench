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
struct TYPE_8__ {int nb_items; TYPE_2__* item; } ;
struct TYPE_7__ {int nb_stream_info; TYPE_1__* stream_info; } ;
struct TYPE_6__ {int id; } ;
typedef  TYPE_1__ MOVFragmentStreamInfo ;
typedef  TYPE_2__ MOVFragmentIndexItem ;
typedef  TYPE_3__ MOVFragmentIndex ;

/* Variables and functions */

__attribute__((used)) static MOVFragmentStreamInfo * get_frag_stream_info(
    MOVFragmentIndex *frag_index,
    int index,
    int id)
{
    int i;
    MOVFragmentIndexItem * item;

    if (index < 0 || index >= frag_index->nb_items)
        return NULL;
    item = &frag_index->item[index];
    for (i = 0; i < item->nb_stream_info; i++)
        if (item->stream_info[i].id == id)
            return &item->stream_info[i];

    // This shouldn't happen
    return NULL;
}