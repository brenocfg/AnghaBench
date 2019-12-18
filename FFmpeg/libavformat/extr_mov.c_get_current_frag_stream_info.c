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
struct TYPE_5__ {size_t current; size_t nb_items; TYPE_1__* item; } ;
struct TYPE_4__ {size_t current; size_t nb_stream_info; int /*<<< orphan*/ * stream_info; } ;
typedef  int /*<<< orphan*/  MOVFragmentStreamInfo ;
typedef  TYPE_1__ MOVFragmentIndexItem ;
typedef  TYPE_2__ MOVFragmentIndex ;

/* Variables and functions */

__attribute__((used)) static MOVFragmentStreamInfo * get_current_frag_stream_info(
    MOVFragmentIndex *frag_index)
{
    MOVFragmentIndexItem *item;
    if (frag_index->current < 0 ||
        frag_index->current >= frag_index->nb_items)
        return NULL;

    item = &frag_index->item[frag_index->current];
    if (item->current >= 0 && item->current < item->nb_stream_info)
        return &item->stream_info[item->current];

    // This shouldn't happen
    return NULL;
}