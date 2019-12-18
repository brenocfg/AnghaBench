#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_4__ {TYPE_1__* phy; } ;
struct bnx2x {TYPE_2__ link_params; } ;
struct TYPE_3__ {int media_type; } ;

/* Variables and functions */
#define  ETH_PHY_BASE_T 136 
#define  ETH_PHY_CX4 135 
#define  ETH_PHY_DA_TWINAX 134 
#define  ETH_PHY_KR 133 
#define  ETH_PHY_NOT_PRESENT 132 
#define  ETH_PHY_SFPP_10G_FIBER 131 
#define  ETH_PHY_SFP_1G_FIBER 130 
#define  ETH_PHY_UNSPECIFIED 129 
#define  ETH_PHY_XFP_FIBER 128 
 int PORT_DA ; 
 int PORT_FIBRE ; 
 int PORT_NONE ; 
 int PORT_OTHER ; 
 int PORT_TP ; 
 size_t bnx2x_get_cur_phy_idx (struct bnx2x*) ; 

__attribute__((used)) static int bnx2x_get_port_type(struct bnx2x *bp)
{
	int port_type;
	u32 phy_idx = bnx2x_get_cur_phy_idx(bp);
	switch (bp->link_params.phy[phy_idx].media_type) {
	case ETH_PHY_SFPP_10G_FIBER:
	case ETH_PHY_SFP_1G_FIBER:
	case ETH_PHY_XFP_FIBER:
	case ETH_PHY_KR:
	case ETH_PHY_CX4:
		port_type = PORT_FIBRE;
		break;
	case ETH_PHY_DA_TWINAX:
		port_type = PORT_DA;
		break;
	case ETH_PHY_BASE_T:
		port_type = PORT_TP;
		break;
	case ETH_PHY_NOT_PRESENT:
		port_type = PORT_NONE;
		break;
	case ETH_PHY_UNSPECIFIED:
	default:
		port_type = PORT_OTHER;
		break;
	}
	return port_type;
}