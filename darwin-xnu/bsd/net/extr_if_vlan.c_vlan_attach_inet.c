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
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ether_attach_inet (struct ifnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
vlan_attach_inet(struct ifnet *ifp, protocol_family_t protocol_family)
{
    return (ether_attach_inet(ifp, protocol_family));
}