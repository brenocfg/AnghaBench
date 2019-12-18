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
typedef  TYPE_1__* vlan_parent_ref ;
struct TYPE_3__ {int /*<<< orphan*/  vlp_vlan_list; } ;

/* Variables and functions */
 int LIST_EMPTY (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ int
vlan_parent_no_vlans(vlan_parent_ref vlp)
{
    return (LIST_EMPTY(&vlp->vlp_vlan_list));
}