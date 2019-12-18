#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {scalar_t__ index; scalar_t__ duration; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_6__ {scalar_t__ feature; int /*<<< orphan*/  list_title; } ;
typedef  TYPE_2__ hb_title_set_t ;
typedef  int gint ;

/* Variables and functions */
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/ * h_scan ; 
 TYPE_2__* hb_get_title_set (int /*<<< orphan*/ *) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_1__* hb_list_item (int /*<<< orphan*/ ,int) ; 

gint
ghb_longest_title()
{
    hb_title_set_t * title_set;
    const hb_title_t * title;
    gint count = 0, ii, longest = -1;
    int64_t duration = 0;

    g_debug("ghb_longest_title ()\n");
    if (h_scan == NULL) return 0;
    title_set = hb_get_title_set( h_scan );
    count = hb_list_count( title_set->list_title );
    if (count < 1) return -1;

    // Check that the feature title in the title_set exists in the list
    // of titles.  If not, pick the longest.
    for (ii = 0; ii < count; ii++)
    {
        title = hb_list_item(title_set->list_title, ii);
        if (title->index == title_set->feature)
            return title_set->feature;
        if (title->duration > duration)
            longest = title->index;
    }
    return longest;
}