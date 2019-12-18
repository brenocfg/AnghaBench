#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int host_roaming; scalar_t__ iw_mode; int /*<<< orphan*/  preferred_ap; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2_host_roaming (TYPE_1__*) ; 

__attribute__((used)) static void handle_info_queue_scanresults(local_info_t *local)
{
	if (local->host_roaming == 1 && local->iw_mode == IW_MODE_INFRA)
		prism2_host_roaming(local);

	if (local->host_roaming == 2 && local->iw_mode == IW_MODE_INFRA &&
	    !is_zero_ether_addr(local->preferred_ap)) {
		/*
		 * Firmware seems to be getting into odd state in host_roaming
		 * mode 2 when hostscan is used without join command, so try
		 * to fix this by re-joining the current AP. This does not
		 * actually trigger a new association if the current AP is
		 * still in the scan results.
		 */
		prism2_host_roaming(local);
	}
}