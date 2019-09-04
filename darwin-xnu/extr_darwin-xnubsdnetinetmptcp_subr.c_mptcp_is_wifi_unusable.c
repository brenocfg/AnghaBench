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
struct mptses {int mpte_flags; } ;
struct TYPE_2__ {int sa_wifi_status; } ;

/* Variables and functions */
 int MPTE_FIRSTPARTY ; 
 int SYMPTOMS_ADVISORY_WIFI_BAD ; 
 TYPE_1__ mptcp_advisory ; 

int
mptcp_is_wifi_unusable(struct mptses *mpte)
{
	if (mpte->mpte_flags & MPTE_FIRSTPARTY) {
		if (mptcp_advisory.sa_wifi_status)
			return ((mptcp_advisory.sa_wifi_status & SYMPTOMS_ADVISORY_WIFI_BAD) ? 1 : 0);

		/*
		 * If it's a first-party app and we don't have any info
		 * about the Wi-Fi state, let's be pessimistic.
		 */
		return (-1);
	}

	return ((mptcp_advisory.sa_wifi_status & SYMPTOMS_ADVISORY_WIFI_BAD) ? 1 : 0);
}