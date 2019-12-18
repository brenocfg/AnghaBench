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
typedef  scalar_t__ ifvlan_ref ;

/* Variables and functions */
 scalar_t__ ifnet_softc (struct ifnet*) ; 

__attribute__((used)) static ifvlan_ref
ifnet_get_ifvlan(struct ifnet * ifp)
{
    ifvlan_ref		ifv;

    ifv = (ifvlan_ref)ifnet_softc(ifp);
    return (ifv);
}