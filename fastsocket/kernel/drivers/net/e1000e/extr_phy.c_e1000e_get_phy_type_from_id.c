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
typedef  int u32 ;
typedef  enum e1000_phy_type { ____Placeholder_e1000_phy_type } e1000_phy_type ;

/* Variables and functions */
#define  BME1000_E_PHY_ID 143 
#define  BME1000_E_PHY_ID_R2 142 
#define  GG82563_E_PHY_ID 141 
#define  I217_E_PHY_ID 140 
#define  I82577_E_PHY_ID 139 
#define  I82578_E_PHY_ID 138 
#define  I82579_E_PHY_ID 137 
#define  IFE_C_E_PHY_ID 136 
#define  IFE_E_PHY_ID 135 
#define  IFE_PLUS_E_PHY_ID 134 
#define  IGP01E1000_I_PHY_ID 133 
#define  IGP03E1000_E_PHY_ID 132 
#define  M88E1000_E_PHY_ID 131 
#define  M88E1000_I_PHY_ID 130 
#define  M88E1011_I_PHY_ID 129 
#define  M88E1111_I_PHY_ID 128 
 int e1000_phy_82577 ; 
 int e1000_phy_82578 ; 
 int e1000_phy_82579 ; 
 int e1000_phy_bm ; 
 int e1000_phy_gg82563 ; 
 int e1000_phy_i217 ; 
 int e1000_phy_ife ; 
 int e1000_phy_igp_2 ; 
 int e1000_phy_igp_3 ; 
 int e1000_phy_m88 ; 
 int e1000_phy_unknown ; 

enum e1000_phy_type e1000e_get_phy_type_from_id(u32 phy_id)
{
	enum e1000_phy_type phy_type = e1000_phy_unknown;

	switch (phy_id) {
	case M88E1000_I_PHY_ID:
	case M88E1000_E_PHY_ID:
	case M88E1111_I_PHY_ID:
	case M88E1011_I_PHY_ID:
		phy_type = e1000_phy_m88;
		break;
	case IGP01E1000_I_PHY_ID:	/* IGP 1 & 2 share this */
		phy_type = e1000_phy_igp_2;
		break;
	case GG82563_E_PHY_ID:
		phy_type = e1000_phy_gg82563;
		break;
	case IGP03E1000_E_PHY_ID:
		phy_type = e1000_phy_igp_3;
		break;
	case IFE_E_PHY_ID:
	case IFE_PLUS_E_PHY_ID:
	case IFE_C_E_PHY_ID:
		phy_type = e1000_phy_ife;
		break;
	case BME1000_E_PHY_ID:
	case BME1000_E_PHY_ID_R2:
		phy_type = e1000_phy_bm;
		break;
	case I82578_E_PHY_ID:
		phy_type = e1000_phy_82578;
		break;
	case I82577_E_PHY_ID:
		phy_type = e1000_phy_82577;
		break;
	case I82579_E_PHY_ID:
		phy_type = e1000_phy_82579;
		break;
	case I217_E_PHY_ID:
		phy_type = e1000_phy_i217;
		break;
	default:
		phy_type = e1000_phy_unknown;
		break;
	}
	return phy_type;
}