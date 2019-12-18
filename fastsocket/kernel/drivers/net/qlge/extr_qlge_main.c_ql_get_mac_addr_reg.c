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
typedef  int u16 ;
struct ql_adapter {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EPERM ; 
 int MAC_ADDR_ADR ; 
 int /*<<< orphan*/  MAC_ADDR_DATA ; 
 int /*<<< orphan*/  MAC_ADDR_IDX ; 
 int MAC_ADDR_IDX_SHIFT ; 
 int /*<<< orphan*/  MAC_ADDR_MR ; 
 int /*<<< orphan*/  MAC_ADDR_MW ; 
 int MAC_ADDR_RS ; 
#define  MAC_ADDR_TYPE_CAM_MAC 131 
#define  MAC_ADDR_TYPE_MULTI_FLTR 130 
#define  MAC_ADDR_TYPE_MULTI_MAC 129 
#define  MAC_ADDR_TYPE_VLAN 128 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_crit (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 void* ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_wait_reg_rdy (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

int ql_get_mac_addr_reg(struct ql_adapter *qdev, u32 type, u16 index,
			u32 *value)
{
	u32 offset = 0;
	int status;

	switch (type) {
	case MAC_ADDR_TYPE_MULTI_MAC:
	case MAC_ADDR_TYPE_CAM_MAC:
		{
			status =
			    ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MW, 0);
			if (status)
				goto exit;
			ql_write32(qdev, MAC_ADDR_IDX, (offset++) | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   MAC_ADDR_ADR | MAC_ADDR_RS | type); /* type */
			status =
			    ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MR, 0);
			if (status)
				goto exit;
			*value++ = ql_read32(qdev, MAC_ADDR_DATA);
			status =
			    ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MW, 0);
			if (status)
				goto exit;
			ql_write32(qdev, MAC_ADDR_IDX, (offset++) | /* offset */
				   (index << MAC_ADDR_IDX_SHIFT) | /* index */
				   MAC_ADDR_ADR | MAC_ADDR_RS | type); /* type */
			status =
			    ql_wait_reg_rdy(qdev,
				MAC_ADDR_IDX, MAC_ADDR_MR, 0);
			if (status)
				goto exit;
			*value++ = ql_read32(qdev, MAC_ADDR_DATA);
			if (type == MAC_ADDR_TYPE_CAM_MAC) {
				status =
				    ql_wait_reg_rdy(qdev,
					MAC_ADDR_IDX, MAC_ADDR_MW, 0);
				if (status)
					goto exit;
				ql_write32(qdev, MAC_ADDR_IDX, (offset++) | /* offset */
					   (index << MAC_ADDR_IDX_SHIFT) | /* index */
					   MAC_ADDR_ADR | MAC_ADDR_RS | type); /* type */
				status =
				    ql_wait_reg_rdy(qdev, MAC_ADDR_IDX,
						    MAC_ADDR_MR, 0);
				if (status)
					goto exit;
				*value++ = ql_read32(qdev, MAC_ADDR_DATA);
			}
			break;
		}
	case MAC_ADDR_TYPE_VLAN:
	case MAC_ADDR_TYPE_MULTI_FLTR:
	default:
		netif_crit(qdev, ifup, qdev->ndev,
			   "Address type %d not yet supported.\n", type);
		status = -EPERM;
	}
exit:
	return status;
}