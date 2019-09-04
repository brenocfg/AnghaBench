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
struct TYPE_4__ {int /*<<< orphan*/  po_actor_state; int /*<<< orphan*/  po_partner_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  bondport_assign_to_LAG (TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lacp_actor_partner_state_set_defaulted (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bondport_RecordDefault(bondport_ref p)
{
    bzero(&p->po_partner_state, sizeof(p->po_partner_state));
    p->po_actor_state 
	= lacp_actor_partner_state_set_defaulted(p->po_actor_state);
    bondport_assign_to_LAG(p);
    return;
}