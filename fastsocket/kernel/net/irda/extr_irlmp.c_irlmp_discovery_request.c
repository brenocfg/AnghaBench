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
struct TYPE_2__ {int /*<<< orphan*/  cachelog; } ;

/* Variables and functions */
 int DISCOVERY_DEFAULT_SLOTS ; 
 int /*<<< orphan*/  DISCOVERY_LOG ; 
 TYPE_1__* irlmp ; 
 int /*<<< orphan*/  irlmp_discovery_confirm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlmp_do_discovery (int) ; 
 int /*<<< orphan*/  sysctl_discovery ; 
 int sysctl_discovery_slots ; 

void irlmp_discovery_request(int nslots)
{
	/* Return current cached discovery log (in full) */
	irlmp_discovery_confirm(irlmp->cachelog, DISCOVERY_LOG);

	/*
	 * Start a single discovery operation if discovery is not already
	 * running
	 */
	if (!sysctl_discovery) {
		/* Check if user wants to override the default */
		if (nslots == DISCOVERY_DEFAULT_SLOTS)
			nslots = sysctl_discovery_slots;

		irlmp_do_discovery(nslots);
		/* Note : we never do expiry here. Expiry will run on the
		 * discovery timer regardless of the state of sysctl_discovery
		 * Jean II */
	}
}