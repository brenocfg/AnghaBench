#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dn_ifaddr {int /*<<< orphan*/  ifa_local; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 int /*<<< orphan*/  RTN_LOCAL ; 
 TYPE_1__* dev ; 
 int /*<<< orphan*/  fib_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dn_ifaddr*) ; 

__attribute__((used)) static void dn_fib_add_ifaddr(struct dn_ifaddr *ifa)
{

	fib_magic(RTM_NEWROUTE, RTN_LOCAL, ifa->ifa_local, 16, ifa);

#if 0
	if (!(dev->flags&IFF_UP))
		return;
	/* In the future, we will want to add default routes here */

#endif
}