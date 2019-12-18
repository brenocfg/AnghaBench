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
typedef  int u64 ;
struct ieee80211_hw {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_PROMISC_IN_BSS ; 
 int /*<<< orphan*/  IEEE80211_HW_RX_INCLUDES_FCS ; 

__attribute__((used)) static void wbsoft_configure_filter(struct ieee80211_hw *dev,
				    unsigned int changed_flags,
				    unsigned int *total_flags,
				    u64 multicast)
{
	unsigned int new_flags;

	new_flags = 0;

	if (*total_flags & FIF_PROMISC_IN_BSS)
		new_flags |= FIF_PROMISC_IN_BSS;
	else if ((*total_flags & FIF_ALLMULTI) || (multicast > 32))
		new_flags |= FIF_ALLMULTI;

	dev->flags &= ~IEEE80211_HW_RX_INCLUDES_FCS;

	*total_flags = new_flags;
}