#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  paging; int /*<<< orphan*/  page_queue; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ btm_cb ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void  btm_acl_reset_paging (void)
{
    BT_HDR *p;
    BTM_TRACE_DEBUG ("btm_acl_reset_paging\n");
    /* If we sent reset we are definitely not paging any more */
    while ((p = (BT_HDR *)fixed_queue_dequeue(btm_cb.page_queue, 0)) != NULL) {
        osi_free (p);
    }

    btm_cb.paging = FALSE;
}