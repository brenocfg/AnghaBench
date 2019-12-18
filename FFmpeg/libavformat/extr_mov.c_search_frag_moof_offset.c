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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int nb_items; TYPE_1__* item; } ;
struct TYPE_4__ {scalar_t__ moof_offset; } ;
typedef  TYPE_2__ MOVFragmentIndex ;

/* Variables and functions */

__attribute__((used)) static int search_frag_moof_offset(MOVFragmentIndex *frag_index, int64_t offset)
{
    int a, b, m;
    int64_t moof_offset;

    // Optimize for appending new entries
    if (!frag_index->nb_items ||
        frag_index->item[frag_index->nb_items - 1].moof_offset < offset)
        return frag_index->nb_items;

    a = -1;
    b = frag_index->nb_items;

    while (b - a > 1) {
        m = (a + b) >> 1;
        moof_offset = frag_index->item[m].moof_offset;
        if (moof_offset >= offset)
            b = m;
        if (moof_offset <= offset)
            a = m;
    }
    return b;
}