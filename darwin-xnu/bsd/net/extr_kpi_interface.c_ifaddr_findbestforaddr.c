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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int /*<<< orphan*/ * ifaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ifaof_ifpforaddr_select (struct sockaddr const*,int /*<<< orphan*/ *) ; 

ifaddr_t
ifaddr_findbestforaddr(const struct sockaddr *addr, ifnet_t interface)
{
	if (addr == NULL || interface == NULL)
		return (NULL);

	return (ifaof_ifpforaddr_select(addr, interface));
}