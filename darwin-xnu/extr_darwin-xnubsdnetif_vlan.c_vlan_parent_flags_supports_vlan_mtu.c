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
struct TYPE_3__ {int vlp_flags; } ;

/* Variables and functions */
 int VLPF_SUPPORTS_VLAN_MTU ; 

__attribute__((used)) static __inline__ int
vlan_parent_flags_supports_vlan_mtu(vlan_parent_ref vlp)
{
    return ((vlp->vlp_flags & VLPF_SUPPORTS_VLAN_MTU) != 0);
}