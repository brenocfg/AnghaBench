#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ifvlan_ref ;

/* Variables and functions */
 scalar_t__ ifvlan_flags_detaching (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifvlan_flags_set_detaching (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_assert_lock_held () ; 
 int /*<<< orphan*/  vlan_unconfig (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vlan_remove(ifvlan_ref ifv, int need_to_wait)
{
    vlan_assert_lock_held();
    if (ifvlan_flags_detaching(ifv)) {
	return (0);
    }
    ifvlan_flags_set_detaching(ifv);
    vlan_unconfig(ifv, need_to_wait);
    return (1);
}