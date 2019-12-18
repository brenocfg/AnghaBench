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
typedef  TYPE_2__* bondport_ref ;
struct TYPE_5__ {int /*<<< orphan*/  po_actor_state; TYPE_1__* po_bond; } ;
struct TYPE_4__ {scalar_t__ ifb_mode; } ;

/* Variables and functions */
 scalar_t__ IF_BOND_MODE_LACP ; 
 int TRUE ; 
 int lacp_actor_partner_state_collecting (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int
bondport_collecting(bondport_ref p)
{
    if (p->po_bond->ifb_mode == IF_BOND_MODE_LACP) {
	return (lacp_actor_partner_state_collecting(p->po_actor_state));
    }
    return (TRUE);
}