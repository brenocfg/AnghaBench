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
struct vlan_parent {int vlp_flags; } ;

/* Variables and functions */
 int VLPF_DETACHING ; 

__attribute__((used)) static __inline__ int
vlan_parent_flags_detaching(struct vlan_parent * vlp)
{
    return ((vlp->vlp_flags & VLPF_DETACHING) != 0);
}