#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  count; TYPE_1__* p_last; TYPE_2__* p_first; } ;
typedef  TYPE_3__ tGATT_HDL_LIST_INFO ;
struct TYPE_10__ {TYPE_2__* p_next; TYPE_1__* p_prev; } ;
typedef  TYPE_4__ tGATT_HDL_LIST_ELEM ;
struct TYPE_8__ {TYPE_1__* p_prev; } ;
struct TYPE_7__ {TYPE_2__* p_next; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN gatt_remove_an_item_from_list(tGATT_HDL_LIST_INFO *p_list, tGATT_HDL_LIST_ELEM *p_remove)
{
    if (!p_remove || !p_list->p_first) {
        GATT_TRACE_DEBUG("p_remove==NULL || p_list->p_first==NULL");
        return FALSE;
    }

    if (p_remove->p_prev == NULL) {
        p_list->p_first             = p_remove->p_next;
        if (p_remove->p_next) {
            p_remove->p_next->p_prev    = NULL;
        }
    } else if (p_remove->p_next == NULL) {
        p_list->p_last              = p_remove->p_prev;
        p_remove->p_prev->p_next    = NULL;
    } else {
        p_remove->p_next->p_prev = p_remove->p_prev;
        p_remove->p_prev->p_next = p_remove->p_next;
    }
    p_list->count--;
    return TRUE;

}