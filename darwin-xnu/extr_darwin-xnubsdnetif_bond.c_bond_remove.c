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
typedef  int /*<<< orphan*/  ifbond_ref ;
struct TYPE_2__ {int /*<<< orphan*/  ifbond_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_assert_lock_held () ; 
 int /*<<< orphan*/  bond_remove_all_interfaces (int /*<<< orphan*/ ) ; 
 TYPE_1__* g_bond ; 
 int /*<<< orphan*/  ifb_bond_list ; 
 int /*<<< orphan*/  ifbond_flags_set_if_detaching (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bond_remove(ifbond_ref ifb)
{
    bond_assert_lock_held();
    ifbond_flags_set_if_detaching(ifb);
    TAILQ_REMOVE(&g_bond->ifbond_list, ifb, ifb_bond_list);
    bond_remove_all_interfaces(ifb);
    return;
}