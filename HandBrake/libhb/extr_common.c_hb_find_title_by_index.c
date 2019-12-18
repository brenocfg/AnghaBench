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
struct TYPE_6__ {int index; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_7__ {int /*<<< orphan*/  list_title; } ;
typedef  TYPE_2__ hb_title_set_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 TYPE_2__* hb_get_title_set (int /*<<< orphan*/ *) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_1__* hb_list_item (int /*<<< orphan*/ ,int) ; 

hb_title_t * hb_find_title_by_index( hb_handle_t *h, int title_index )
{
    hb_title_set_t *title_set = hb_get_title_set( h );
    int ii;

    for (ii = 0; ii < hb_list_count(title_set->list_title); ii++)
    {
        hb_title_t *title = hb_list_item(title_set->list_title, ii);
        if (title_index == title->index)
        {
            return title;
        }
    }
    return NULL;
}