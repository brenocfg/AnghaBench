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
struct TYPE_3__ {int /*<<< orphan*/  vlp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLPF_LINK_EVENT_REQUIRED ; 

__attribute__((used)) static __inline__ void
vlan_parent_flags_set_link_event_required(vlan_parent_ref vlp)
{
    vlp->vlp_flags |= VLPF_LINK_EVENT_REQUIRED;
    return;
}