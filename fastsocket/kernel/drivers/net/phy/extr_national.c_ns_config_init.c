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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_FALLBACK_ON ; 
 int /*<<< orphan*/  hdx_loopback_off ; 
 int /*<<< orphan*/  ns_10_base_t_hdx_loopack (struct phy_device*,int /*<<< orphan*/ ) ; 
 int ns_ack_interrupt (struct phy_device*) ; 
 int /*<<< orphan*/  ns_giga_speed_fallback (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ns_config_init(struct phy_device *phydev)
{
	ns_giga_speed_fallback(phydev, ALL_FALLBACK_ON);
	/* In the latest MAC or switches design, the 10 Mbps loopback
	   is desired to be turned off. */
	ns_10_base_t_hdx_loopack(phydev, hdx_loopback_off);
	return ns_ack_interrupt(phydev);
}