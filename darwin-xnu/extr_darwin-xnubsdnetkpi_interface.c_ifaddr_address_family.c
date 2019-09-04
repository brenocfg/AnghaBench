#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  TYPE_2__* ifaddr_t ;
struct TYPE_7__ {TYPE_1__* ifa_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_LOCK_SPIN (TYPE_2__*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (TYPE_2__*) ; 

sa_family_t
ifaddr_address_family(ifaddr_t ifa)
{
	sa_family_t family = 0;

	if (ifa != NULL) {
		IFA_LOCK_SPIN(ifa);
		if (ifa->ifa_addr != NULL)
			family = ifa->ifa_addr->sa_family;
		IFA_UNLOCK(ifa);
	}
	return (family);
}