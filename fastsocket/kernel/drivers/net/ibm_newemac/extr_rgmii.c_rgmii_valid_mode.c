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

/* Variables and functions */
 int PHY_MODE_GMII ; 
 int PHY_MODE_MII ; 
 int PHY_MODE_RGMII ; 
 int PHY_MODE_RTBI ; 
 int PHY_MODE_TBI ; 

__attribute__((used)) static inline int rgmii_valid_mode(int phy_mode)
{
	return  phy_mode == PHY_MODE_GMII ||
		phy_mode == PHY_MODE_MII ||
		phy_mode == PHY_MODE_RGMII ||
		phy_mode == PHY_MODE_TBI ||
		phy_mode == PHY_MODE_RTBI;
}