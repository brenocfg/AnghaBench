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
typedef  int /*<<< orphan*/ * vlan_parent_ref ;
typedef  TYPE_1__* ifvlan_ref ;
struct TYPE_3__ {int /*<<< orphan*/ * ifv_vlp; } ;

/* Variables and functions */
 scalar_t__ vlan_parent_flags_detaching (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_parent_retain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vlan_parent_ref
ifvlan_get_vlan_parent_retained(ifvlan_ref ifv)
{
    vlan_parent_ref	vlp = ifv->ifv_vlp;

    if (vlp == NULL || vlan_parent_flags_detaching(vlp)) {
	return (NULL);
    }
    vlan_parent_retain(vlp);
    return (vlp);
}