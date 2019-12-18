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
struct irda_device_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  cachelog; } ;

/* Variables and functions */
 int DISCOVERY_DEFAULT_SLOTS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* irlmp ; 
 struct irda_device_info* irlmp_copy_discoveries (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlmp_do_discovery (int) ; 
 int /*<<< orphan*/  sysctl_discovery ; 
 int sysctl_discovery_slots ; 

struct irda_device_info *irlmp_get_discoveries(int *pn, __u16 mask, int nslots)
{
	/* If discovery is not enabled, it's likely that the discovery log
	 * will be empty. So, we trigger a single discovery, so that next
	 * time the user call us there might be some results in the log.
	 * Jean II
	 */
	if (!sysctl_discovery) {
		/* Check if user wants to override the default */
		if (nslots == DISCOVERY_DEFAULT_SLOTS)
			nslots = sysctl_discovery_slots;

		/* Start discovery - will complete sometime later */
		irlmp_do_discovery(nslots);
		/* Note : we never do expiry here. Expiry will run on the
		 * discovery timer regardless of the state of sysctl_discovery
		 * Jean II */
	}

	/* Return current cached discovery log */
	return(irlmp_copy_discoveries(irlmp->cachelog, pn, mask, TRUE));
}