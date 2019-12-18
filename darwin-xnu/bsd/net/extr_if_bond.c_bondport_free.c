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
typedef  TYPE_1__* bondport_ref ;
struct TYPE_4__ {int /*<<< orphan*/  po_transmit_timer; int /*<<< orphan*/  po_wait_while_timer; int /*<<< orphan*/  po_periodic_timer; int /*<<< orphan*/  po_current_while_timer; int /*<<< orphan*/  po_multicast; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_BOND ; 
 int /*<<< orphan*/  devtimer_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multicast_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bondport_free(bondport_ref p)
{
    multicast_list_remove(&p->po_multicast);
    devtimer_release(p->po_current_while_timer);
    devtimer_release(p->po_periodic_timer);
    devtimer_release(p->po_wait_while_timer);
    devtimer_release(p->po_transmit_timer);
    FREE(p, M_BOND);
    return;
}