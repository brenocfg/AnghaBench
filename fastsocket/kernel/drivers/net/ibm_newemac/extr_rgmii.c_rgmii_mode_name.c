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
 int /*<<< orphan*/  BUG () ; 
#define  PHY_MODE_GMII 132 
#define  PHY_MODE_MII 131 
#define  PHY_MODE_RGMII 130 
#define  PHY_MODE_RTBI 129 
#define  PHY_MODE_TBI 128 

__attribute__((used)) static inline const char *rgmii_mode_name(int mode)
{
	switch (mode) {
	case PHY_MODE_RGMII:
		return "RGMII";
	case PHY_MODE_TBI:
		return "TBI";
	case PHY_MODE_GMII:
		return "GMII";
	case PHY_MODE_MII:
		return "MII";
	case PHY_MODE_RTBI:
		return "RTBI";
	default:
		BUG();
	}
}