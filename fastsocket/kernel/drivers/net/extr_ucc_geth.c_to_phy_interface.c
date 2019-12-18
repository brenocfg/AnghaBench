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
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_ID ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_RXID ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_TXID ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RTBI ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_TBI ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static phy_interface_t to_phy_interface(const char *phy_connection_type)
{
	if (strcasecmp(phy_connection_type, "mii") == 0)
		return PHY_INTERFACE_MODE_MII;
	if (strcasecmp(phy_connection_type, "gmii") == 0)
		return PHY_INTERFACE_MODE_GMII;
	if (strcasecmp(phy_connection_type, "tbi") == 0)
		return PHY_INTERFACE_MODE_TBI;
	if (strcasecmp(phy_connection_type, "rmii") == 0)
		return PHY_INTERFACE_MODE_RMII;
	if (strcasecmp(phy_connection_type, "rgmii") == 0)
		return PHY_INTERFACE_MODE_RGMII;
	if (strcasecmp(phy_connection_type, "rgmii-id") == 0)
		return PHY_INTERFACE_MODE_RGMII_ID;
	if (strcasecmp(phy_connection_type, "rgmii-txid") == 0)
		return PHY_INTERFACE_MODE_RGMII_TXID;
	if (strcasecmp(phy_connection_type, "rgmii-rxid") == 0)
		return PHY_INTERFACE_MODE_RGMII_RXID;
	if (strcasecmp(phy_connection_type, "rtbi") == 0)
		return PHY_INTERFACE_MODE_RTBI;
	if (strcasecmp(phy_connection_type, "sgmii") == 0)
		return PHY_INTERFACE_MODE_SGMII;

	return PHY_INTERFACE_MODE_MII;
}