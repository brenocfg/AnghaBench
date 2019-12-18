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
struct TYPE_7__ {int /*<<< orphan*/  count; TYPE_3__* p_first; TYPE_3__* p_last; } ;
typedef  TYPE_2__ tGATT_HDL_LIST_INFO ;
struct TYPE_6__ {scalar_t__ s_handle; } ;
struct TYPE_8__ {struct TYPE_8__* p_next; struct TYPE_8__* p_prev; TYPE_1__ asgn_range; } ;
typedef  TYPE_3__ tGATT_HDL_LIST_ELEM ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN gatt_add_an_item_to_list(tGATT_HDL_LIST_INFO *p_list, tGATT_HDL_LIST_ELEM *p_new)
{
    tGATT_HDL_LIST_ELEM *p_old;
    if (!p_new) {
        GATT_TRACE_DEBUG("p_new==NULL");
        return FALSE;
    }

    if (!p_list->p_first) {
        /* this is an empty list */
        p_list->p_first =
            p_list->p_last  = p_new;
        p_new->p_next   =
            p_new->p_prev   = NULL;
    } else {
        p_old = p_list->p_first;
        while (1) {
            if (p_old == NULL) {
                p_list->p_last->p_next      = p_new;
                p_new->p_prev               = p_list->p_last;
                p_new->p_next               = NULL;
                p_list->p_last              = p_new;

                break;

            } else {
                if (p_new->asgn_range.s_handle >  p_old->asgn_range.s_handle) {
                    if (p_old == p_list->p_first) {
                        p_list->p_first = p_new;
                    }

                    p_new->p_prev    = p_old->p_prev;
                    p_new->p_next    = p_old;


                    p_old->p_prev    = p_new;
                    break;
                }
            }
            p_old = p_old->p_next;
        }
    }
    p_list->count++;
    return TRUE;

}