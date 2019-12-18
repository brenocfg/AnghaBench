#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_4__ {int id; } ;
typedef  TYPE_1__ hb_filter_object_t ;

/* Variables and functions */
 int hb_list_count (int /*<<< orphan*/  const*) ; 
 TYPE_1__* hb_list_item (int /*<<< orphan*/  const*,int) ; 

hb_filter_object_t * hb_filter_find(const hb_list_t *list, int filter_id)
{
    hb_filter_object_t *filter = NULL;
    int ii;

    if (list == NULL)
    {
        return NULL;
    }
    for (ii = 0; ii < hb_list_count(list); ii++)
    {
        filter = hb_list_item(list, ii);
        if (filter->id == filter_id)
        {
            return filter;
        }
    }

    return NULL;
}