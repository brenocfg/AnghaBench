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
typedef  int /*<<< orphan*/ * vlan_parent_ref ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/ * ifvlan_ref ;

/* Variables and functions */
 int /*<<< orphan*/ * parent_list_lookup (struct ifnet*) ; 
 int /*<<< orphan*/ * vlan_parent_lookup_tag (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ifvlan_ref 
vlan_lookup_parent_and_tag(struct ifnet * p, int tag)
{
    vlan_parent_ref	vlp;

    vlp = parent_list_lookup(p);
    if (vlp != NULL) {
	return (vlan_parent_lookup_tag(vlp, tag));
    }
    return (NULL);
}