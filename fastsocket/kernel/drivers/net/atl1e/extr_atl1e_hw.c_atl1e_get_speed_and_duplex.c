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
typedef  int u16 ;
struct atl1e_hw {int dummy; } ;

/* Variables and functions */
 int AT_ERR_PHY_RES ; 
 int AT_ERR_PHY_SPEED ; 
 int FULL_DUPLEX ; 
 int HALF_DUPLEX ; 
 int /*<<< orphan*/  MII_AT001_PSSR ; 
#define  MII_AT001_PSSR_1000MBS 130 
#define  MII_AT001_PSSR_100MBS 129 
#define  MII_AT001_PSSR_10MBS 128 
 int MII_AT001_PSSR_DPLX ; 
 int MII_AT001_PSSR_SPD_DPLX_RESOLVED ; 
 int MII_AT001_PSSR_SPEED ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int atl1e_read_phy_reg (struct atl1e_hw*,int /*<<< orphan*/ ,int*) ; 

int atl1e_get_speed_and_duplex(struct atl1e_hw *hw, u16 *speed, u16 *duplex)
{
	int err;
	u16 phy_data;

	/* Read   PHY Specific Status Register (17) */
	err = atl1e_read_phy_reg(hw, MII_AT001_PSSR, &phy_data);
	if (err)
		return err;

	if (!(phy_data & MII_AT001_PSSR_SPD_DPLX_RESOLVED))
		return AT_ERR_PHY_RES;

	switch (phy_data & MII_AT001_PSSR_SPEED) {
	case MII_AT001_PSSR_1000MBS:
		*speed = SPEED_1000;
		break;
	case MII_AT001_PSSR_100MBS:
		*speed = SPEED_100;
		break;
	case MII_AT001_PSSR_10MBS:
		*speed = SPEED_10;
		break;
	default:
		return AT_ERR_PHY_SPEED;
		break;
	}

	if (phy_data & MII_AT001_PSSR_DPLX)
		*duplex = FULL_DUPLEX;
	else
		*duplex = HALF_DUPLEX;

	return 0;
}