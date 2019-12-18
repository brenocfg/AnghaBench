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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct cnic_local {int /*<<< orphan*/  pfid; } ;
struct cnic_dev {int /*<<< orphan*/ * mac_addr; int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ BAR_XSTRORM_INTMEM ; 
 int /*<<< orphan*/  CNIC_WR8 (struct cnic_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TSTORM_ISCSI_TCP_VARS_LSB_LOCAL_MAC_ADDR_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ TSTORM_ISCSI_TCP_VARS_MID_LOCAL_MAC_ADDR_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ TSTORM_ISCSI_TCP_VARS_MSB_LOCAL_MAC_ADDR_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_LOCAL_MAC_ADDR0_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_LOCAL_MAC_ADDR1_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_LOCAL_MAC_ADDR2_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_LOCAL_MAC_ADDR3_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_LOCAL_MAC_ADDR4_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ XSTORM_ISCSI_LOCAL_MAC_ADDR5_OFFSET (int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_init_bnx2x_mac(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	u32 pfid = cp->pfid;
	u8 *mac = dev->mac_addr;

	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR0_OFFSET(pfid), mac[0]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR1_OFFSET(pfid), mac[1]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR2_OFFSET(pfid), mac[2]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR3_OFFSET(pfid), mac[3]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR4_OFFSET(pfid), mac[4]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR5_OFFSET(pfid), mac[5]);

	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_LSB_LOCAL_MAC_ADDR_OFFSET(pfid), mac[5]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_LSB_LOCAL_MAC_ADDR_OFFSET(pfid) + 1,
		 mac[4]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_MID_LOCAL_MAC_ADDR_OFFSET(pfid), mac[3]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_MID_LOCAL_MAC_ADDR_OFFSET(pfid) + 1,
		 mac[2]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_MSB_LOCAL_MAC_ADDR_OFFSET(pfid), mac[1]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_MSB_LOCAL_MAC_ADDR_OFFSET(pfid) + 1,
		 mac[0]);
}