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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpphy_tx_pctl_init_hw (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_tx_pctl_init_sw (struct b43_wldev*) ; 

__attribute__((used)) static void lpphy_tx_pctl_init(struct b43_wldev *dev)
{
	if (0/*FIXME HWPCTL capable */) {
		lpphy_tx_pctl_init_hw(dev);
	} else { /* This device is only software TX power control capable. */
		lpphy_tx_pctl_init_sw(dev);
	}
}