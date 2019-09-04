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
struct ifaddr {scalar_t__ ifa_addr; } ;
typedef  TYPE_1__* ifnet_t ;
struct TYPE_3__ {struct ifaddr* if_lladdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_LOCK_SPIN (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 void* LLADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL (void*) ; 

void *
ifnet_lladdr(ifnet_t interface)
{
	struct ifaddr *ifa;
	void *lladdr;

	if (interface == NULL)
		return (NULL);

	/*
	 * if_lladdr points to the permanent link address of
	 * the interface and it never gets deallocated; internal
	 * code should simply use IF_LLADDR() for performance.
	 */
	ifa = interface->if_lladdr;
	IFA_LOCK_SPIN(ifa);
	lladdr = LLADDR(SDL((void *)ifa->ifa_addr));
	IFA_UNLOCK(ifa);

	return (lladdr);
}