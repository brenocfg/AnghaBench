#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int index; } ;
typedef  TYPE_1__ hb_title_t ;
typedef  int /*<<< orphan*/  hb_list_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_get_titles (int /*<<< orphan*/ *) ; 
 int hb_list_count (int /*<<< orphan*/ *) ; 
 TYPE_1__* hb_list_item (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lookup_title_index(hb_handle_t *h, int title_id)
{
    if (h == NULL)
        return -1;

    hb_list_t *list;
    const hb_title_t *title;
    int count, ii;

    list = hb_get_titles(h);
    count = hb_list_count(list);
    for (ii = 0; ii < count; ii++)
    {
        title = hb_list_item(list, ii);
        if (title_id == title->index)
        {
            return ii;
        }
    }
    return -1;
}