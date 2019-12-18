#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlan_parent_ref ;
typedef  TYPE_2__* ifvlan_ref ;
struct TYPE_7__ {int ifv_tag; TYPE_1__* ifv_vlp; } ;
struct TYPE_6__ {int /*<<< orphan*/  vlp_vlan_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifv_vlan_list ; 

__attribute__((used)) static void
vlan_parent_add_vlan(vlan_parent_ref vlp, ifvlan_ref ifv, int tag)
{
    LIST_INSERT_HEAD(&vlp->vlp_vlan_list, ifv, ifv_vlan_list);
    ifv->ifv_vlp = vlp;
    ifv->ifv_tag = tag;
    return;
}