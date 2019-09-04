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
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/ * ifvlan_ref ;

/* Variables and functions */
 int /*<<< orphan*/ * ifnet_get_ifvlan (struct ifnet*) ; 
 scalar_t__ ifvlan_flags_detaching (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifvlan_retain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ifvlan_ref
ifnet_get_ifvlan_retained(struct ifnet * ifp)
{
    ifvlan_ref		ifv;

    ifv = ifnet_get_ifvlan(ifp);
    if (ifv == NULL) {
	return (NULL);
    }
    if (ifvlan_flags_detaching(ifv)) {
	return (NULL);
    }
    ifvlan_retain(ifv);
    return (ifv);
}