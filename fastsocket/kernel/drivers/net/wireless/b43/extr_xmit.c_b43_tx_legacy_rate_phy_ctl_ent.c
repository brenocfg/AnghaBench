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
typedef  scalar_t__ u8 ;
struct b43_tx_legacy_rate_phy_ctl_entry {scalar_t__ bitrate; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct b43_tx_legacy_rate_phy_ctl_entry*) ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 struct b43_tx_legacy_rate_phy_ctl_entry* b43_tx_legacy_rate_phy_ctl ; 

__attribute__((used)) static const struct b43_tx_legacy_rate_phy_ctl_entry *
b43_tx_legacy_rate_phy_ctl_ent(u8 bitrate)
{
	const struct b43_tx_legacy_rate_phy_ctl_entry *e;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(b43_tx_legacy_rate_phy_ctl); i++) {
		e = &(b43_tx_legacy_rate_phy_ctl[i]);
		if (e->bitrate == bitrate)
			return e;
	}

	B43_WARN_ON(1);
	return NULL;
}