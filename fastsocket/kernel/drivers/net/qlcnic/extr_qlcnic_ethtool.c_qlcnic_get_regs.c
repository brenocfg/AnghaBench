#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qlcnic_recv_context {struct qlcnic_host_sds_ring* sds_rings; TYPE_4__* rds_rings; } ;
struct qlcnic_host_sds_ring {int /*<<< orphan*/  crb_sts_consumer; } ;
struct qlcnic_adapter {int max_sds_rings; TYPE_3__* tx_ring; int /*<<< orphan*/  state; TYPE_2__* pdev; TYPE_1__* ahw; struct qlcnic_recv_context* recv_ctx; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int version; } ;
struct TYPE_8__ {int /*<<< orphan*/  crb_rcv_producer; } ;
struct TYPE_7__ {int /*<<< orphan*/  crb_cmd_producer; int /*<<< orphan*/ * hw_consumer; } ;
struct TYPE_6__ {int device; } ;
struct TYPE_5__ {int revision_id; } ;

/* Variables and functions */
 int QLCNIC_DEV_INFO_SIZE ; 
 int QLCNIC_ETHTOOL_REGS_VER ; 
 int QLCNIC_MGMT_API_VERSION ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_82xx_get_registers (struct qlcnic_adapter*,int*) ; 
 int qlcnic_83xx_get_registers (struct qlcnic_adapter*,int*) ; 
 int /*<<< orphan*/  qlcnic_get_regs_len (struct net_device*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlcnic_get_regs(struct net_device *dev, struct ethtool_regs *regs, void *p)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	struct qlcnic_host_sds_ring *sds_ring;
	u32 *regs_buff = p;
	int ring, i = 0;

	memset(p, 0, qlcnic_get_regs_len(dev));

	regs->version = (QLCNIC_ETHTOOL_REGS_VER << 24) |
		(adapter->ahw->revision_id << 16) | (adapter->pdev)->device;

	regs_buff[0] = (0xcafe0000 | (QLCNIC_DEV_INFO_SIZE & 0xffff));
	regs_buff[1] = QLCNIC_MGMT_API_VERSION;

	if (qlcnic_82xx_check(adapter))
		i = qlcnic_82xx_get_registers(adapter, regs_buff);
	else
		i = qlcnic_83xx_get_registers(adapter, regs_buff);

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		return;

	regs_buff[i++] = 0xFFEFCDAB; /* Marker btw regs and ring count*/

	regs_buff[i++] = 1; /* No. of tx ring */
	regs_buff[i++] = le32_to_cpu(*(adapter->tx_ring->hw_consumer));
	regs_buff[i++] = readl(adapter->tx_ring->crb_cmd_producer);

	regs_buff[i++] = 2; /* No. of rx ring */
	regs_buff[i++] = readl(recv_ctx->rds_rings[0].crb_rcv_producer);
	regs_buff[i++] = readl(recv_ctx->rds_rings[1].crb_rcv_producer);

	regs_buff[i++] = adapter->max_sds_rings;

	for (ring = 0; ring < adapter->max_sds_rings; ring++) {
		sds_ring = &(recv_ctx->sds_rings[ring]);
		regs_buff[i++] = readl(sds_ring->crb_sts_consumer);
	}
}