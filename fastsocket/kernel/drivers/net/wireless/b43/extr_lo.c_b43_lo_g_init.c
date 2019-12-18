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
 int /*<<< orphan*/  b43_gphy_dc_lt_init (struct b43_wldev*,int) ; 
 scalar_t__ b43_has_hardware_pctl (struct b43_wldev*) ; 
 int /*<<< orphan*/  lo_read_power_vector (struct b43_wldev*) ; 

void b43_lo_g_init(struct b43_wldev *dev)
{
	if (b43_has_hardware_pctl(dev)) {
		lo_read_power_vector(dev);
		b43_gphy_dc_lt_init(dev, 1);
	}
}