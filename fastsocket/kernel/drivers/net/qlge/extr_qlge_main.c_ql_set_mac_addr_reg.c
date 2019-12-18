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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ql_adapter {int func; int /*<<< orphan*/  ndev; int /*<<< orphan*/  vlgrp; } ;

/* Variables and functions */
 int CAM_OUT_CQ_ID_SHIFT ; 
 int CAM_OUT_FUNC_SHIFT ; 
 int CAM_OUT_ROUTE_NIC ; 
 int CAM_OUT_RV ; 
 int EPERM ; 
 int /*<<< orphan*/  MAC_ADDR_DATA ; 
 int MAC_ADDR_E ; 
 int /*<<< orphan*/  MAC_ADDR_IDX ; 
 int MAC_ADDR_IDX_SHIFT ; 
 int /*<<< orphan*/  MAC_ADDR_MW ; 
#define  MAC_ADDR_TYPE_CAM_MAC 131 
#define  MAC_ADDR_TYPE_MULTI_FLTR 130 
#define  MAC_ADDR_TYPE_MULTI_MAC 129 
#define  MAC_ADDR_TYPE_VLAN 128 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_crit (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int ql_wait_reg_rdy (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ql_set_mac_addr_reg(struct ql_adapter *qdev, u8 *addr, u32 type,
			       u16 index)
{
	u32 offset = 0;
	int status = 0;

	switch (type) {
	case MAC_ADDR_TYPE_MULTI_MAC:
		{
			u32 upper = (addr[0] << 8) | addr[1];
			u32 lower = (addr[2] << 24) | (addr[3] << 16) |
					(addr[4] << 8) | (addr[5]);

			status =
				ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MW, 0);
			if (status)
				goto exit;
			ql_write32(qdev, MAC_ADDR_IDX, (offset++) |
				(index << MAC_ADDR_IDX_SHIFT) |
				type | MAC_ADDR_E);
			ql_write32(qdev, MAC_ADDR_DATA, lower);
			status =
				ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MW, 0);
			if (status)
				goto exit;
			ql_write32(qdev, MAC_ADDR_IDX, (offset++) |
				(index << MAC_ADDR_IDX_SHIFT) |
				type | MAC_ADDR_E);

			ql_write32(qdev, MAC_ADDR_DATA, upper);
			status =
				ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MW, 0);
			if (status)
				goto exit;
			break;
		}
	case MAC_ADDR_TYPE_CAM_MAC:
		{
			u32 cam_output;
			u32 upper = (addr[0] << 8) | addr[1];
			u32 lower =
			    (addr[2] << 24) | (addr[3] << 16) | (addr[4] << 8) |
			    (addr[5]);
			status =
			    ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MW, 0);
			if (status)
				goto exit;
			ql_write32(qdev, MAC_ADDR_IDX, (offset++) | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   type);	/* type */
			ql_write32(qdev, MAC_ADDR_DATA, lower);
			status =
			    ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MW, 0);
			if (status)
				goto exit;
			ql_write32(qdev, MAC_ADDR_IDX, (offset++) | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   type);	/* type */
			ql_write32(qdev, MAC_ADDR_DATA, upper);
			status =
			    ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MW, 0);
			if (status)
				goto exit;
			ql_write32(qdev, MAC_ADDR_IDX, (offset) |	/* offset */
				   (index << MAC_ADDR_IDX_SHIFT) |	/* index */
				   type);	/* type */
			/* This field should also include the queue id
			   and possibly the function id.  Right now we hardcode
			   the route field to NIC core.
			 */
			cam_output = (CAM_OUT_ROUTE_NIC |
				      (qdev->
				       func << CAM_OUT_FUNC_SHIFT) |
					(0 << CAM_OUT_CQ_ID_SHIFT));
			if (qdev->vlgrp)
				cam_output |= CAM_OUT_RV;
			/* route to NIC core */
			ql_write32(qdev, MAC_ADDR_DATA, cam_output);
			break;
		}
	case MAC_ADDR_TYPE_VLAN:
		{
			u32 enable_bit = *((u32 *) &addr[0]);
			/* For VLAN, the addr actually holds a bit that
			 * either enables or disables the vlan id we are
			 * addressing. It's either MAC_ADDR_E on or off.
			 * That's bit-27 we're talking about.
			 */
			status =
			    ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MW, 0);
			if (status)
				goto exit;
			ql_write32(qdev, MAC_ADDR_IDX, offset |	/* offset */
				   (index << MAC_ADDR_IDX_SHIFT) |	/* index */
				   type |	/* type */
				   enable_bit);	/* enable/disable */
			break;
		}
	case MAC_ADDR_TYPE_MULTI_FLTR:
	default:
		netif_crit(qdev, ifup, qdev->ndev,
			   "Address type %d not yet supported.\n", type);
		status = -EPERM;
	}
exit:
	return status;
}