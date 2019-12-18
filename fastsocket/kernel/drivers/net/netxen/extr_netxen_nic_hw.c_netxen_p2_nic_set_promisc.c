#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ board_type; } ;
struct netxen_adapter {int physical_port; TYPE_1__ ahw; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NETXEN_BRDTYPE_P2_SB31_10G_HMEZ ; 
 scalar_t__ NETXEN_BRDTYPE_P2_SB31_10G_IMEZ ; 
 int NETXEN_NIU_ALLMULTI_MODE ; 
 scalar_t__ NETXEN_NIU_FRAME_COUNT ; 
 scalar_t__ NETXEN_NIU_FRAME_COUNT_SELECT ; 
 int NETXEN_NIU_MAX_XG_PORTS ; 
 int NETXEN_NIU_PROMISC_MODE ; 
 scalar_t__ NETXEN_NIU_XGE_CONFIG_0 ; 
 scalar_t__ NETXEN_NIU_XGE_CONFIG_1 ; 
 int NXRD32 (struct netxen_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int netxen_p2_nic_set_promisc(struct netxen_adapter *adapter, u32 mode)
{
	u32 mac_cfg;
	u32 cnt = 0;
	__u32 reg = 0x0200;
	u32 port = adapter->physical_port;
	u16 board_type = adapter->ahw.board_type;

	if (port >= NETXEN_NIU_MAX_XG_PORTS)
		return -EINVAL;

	mac_cfg = NXRD32(adapter, NETXEN_NIU_XGE_CONFIG_0 + (0x10000 * port));
	mac_cfg &= ~0x4;
	NXWR32(adapter, NETXEN_NIU_XGE_CONFIG_0 + (0x10000 * port), mac_cfg);

	if ((board_type == NETXEN_BRDTYPE_P2_SB31_10G_IMEZ) ||
			(board_type == NETXEN_BRDTYPE_P2_SB31_10G_HMEZ))
		reg = (0x20 << port);

	NXWR32(adapter, NETXEN_NIU_FRAME_COUNT_SELECT, reg);

	mdelay(10);

	while (NXRD32(adapter, NETXEN_NIU_FRAME_COUNT) && ++cnt < 20)
		mdelay(10);

	if (cnt < 20) {

		reg = NXRD32(adapter,
			NETXEN_NIU_XGE_CONFIG_1 + (0x10000 * port));

		if (mode == NETXEN_NIU_PROMISC_MODE)
			reg = (reg | 0x2000UL);
		else
			reg = (reg & ~0x2000UL);

		if (mode == NETXEN_NIU_ALLMULTI_MODE)
			reg = (reg | 0x1000UL);
		else
			reg = (reg & ~0x1000UL);

		NXWR32(adapter,
			NETXEN_NIU_XGE_CONFIG_1 + (0x10000 * port), reg);
	}

	mac_cfg |= 0x4;
	NXWR32(adapter, NETXEN_NIU_XGE_CONFIG_0 + (0x10000 * port), mac_cfg);

	return 0;
}