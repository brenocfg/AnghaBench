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
struct nx_host_sds_ring {int /*<<< orphan*/  crb_sts_consumer; } ;
struct netxen_recv_context {struct nx_host_sds_ring* sds_rings; TYPE_4__* rds_rings; } ;
struct TYPE_6__ {int revision_id; } ;
struct netxen_adapter {int physical_port; scalar_t__ is_up; int max_sds_rings; TYPE_3__* tx_ring; TYPE_2__ ahw; int /*<<< orphan*/  crb_int_state_reg; TYPE_1__* pdev; struct netxen_recv_context recv_ctx; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int version; } ;
struct TYPE_8__ {int /*<<< orphan*/  crb_rcv_producer; } ;
struct TYPE_7__ {int /*<<< orphan*/  crb_cmd_producer; int /*<<< orphan*/  crb_cmd_consumer; int /*<<< orphan*/ * hw_consumer; } ;
struct TYPE_5__ {int device; } ;

/* Variables and functions */
 scalar_t__ CRB_CMDPEG_STATE ; 
 scalar_t__ CRB_FW_CAPABILITIES_1 ; 
 scalar_t__ CRB_RCVPEG_STATE ; 
 scalar_t__ CRB_XG_STATE ; 
 scalar_t__ CRB_XG_STATE_P3 ; 
 scalar_t__ NETXEN_ADAPTER_UP_MAGIC ; 
 scalar_t__ NETXEN_CRB_PEG_NET_0 ; 
 scalar_t__ NETXEN_CRB_PEG_NET_1 ; 
 scalar_t__ NETXEN_CRB_PEG_NET_2 ; 
 scalar_t__ NETXEN_CRB_PEG_NET_3 ; 
 scalar_t__ NETXEN_CRB_PEG_NET_4 ; 
 int /*<<< orphan*/  NETXEN_NIC_REGS_LEN ; 
 scalar_t__ NETXEN_NIU_XGE_CONFIG_0 ; 
 scalar_t__ NETXEN_NIU_XGE_CONFIG_1 ; 
 scalar_t__ NETXEN_PEG_ALIVE_COUNTER ; 
 scalar_t__ NETXEN_PEG_HALT_STATUS1 ; 
 scalar_t__ NETXEN_PEG_HALT_STATUS2 ; 
 int NXRD32 (struct netxen_adapter*,scalar_t__) ; 
 int NXRDIO (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ NX_CRB_DEV_REF_COUNT ; 
 scalar_t__ NX_CRB_DEV_STATE ; 
 scalar_t__ NX_IS_REVISION_P3 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
netxen_nic_get_regs(struct net_device *dev, struct ethtool_regs *regs, void *p)
{
	struct netxen_adapter *adapter = netdev_priv(dev);
	struct netxen_recv_context *recv_ctx = &adapter->recv_ctx;
	struct nx_host_sds_ring *sds_ring;
	u32 *regs_buff = p;
	int ring, i = 0;
	int port = adapter->physical_port;

	memset(p, 0, NETXEN_NIC_REGS_LEN);

	regs->version = (1 << 24) | (adapter->ahw.revision_id << 16) |
	    (adapter->pdev)->device;

	if (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		return;

	regs_buff[i++] = NXRD32(adapter, CRB_CMDPEG_STATE);
	regs_buff[i++] = NXRD32(adapter, CRB_RCVPEG_STATE);
	regs_buff[i++] = NXRD32(adapter, CRB_FW_CAPABILITIES_1);
	regs_buff[i++] = NXRDIO(adapter, adapter->crb_int_state_reg);
	regs_buff[i++] = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);
	regs_buff[i++] = NXRD32(adapter, NX_CRB_DEV_STATE);
	regs_buff[i++] = NXRD32(adapter, NETXEN_PEG_ALIVE_COUNTER);
	regs_buff[i++] = NXRD32(adapter, NETXEN_PEG_HALT_STATUS1);
	regs_buff[i++] = NXRD32(adapter, NETXEN_PEG_HALT_STATUS2);

	regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_0+0x3c);
	regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_1+0x3c);
	regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_2+0x3c);
	regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_3+0x3c);

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id)) {

		regs_buff[i++] = NXRD32(adapter, NETXEN_CRB_PEG_NET_4+0x3c);
		i += 2;

		regs_buff[i++] = NXRD32(adapter, CRB_XG_STATE_P3);
		regs_buff[i++] = le32_to_cpu(*(adapter->tx_ring->hw_consumer));

	} else {
		i++;

		regs_buff[i++] = NXRD32(adapter,
					NETXEN_NIU_XGE_CONFIG_0+(0x10000*port));
		regs_buff[i++] = NXRD32(adapter,
					NETXEN_NIU_XGE_CONFIG_1+(0x10000*port));

		regs_buff[i++] = NXRD32(adapter, CRB_XG_STATE);
		regs_buff[i++] = NXRDIO(adapter,
				 adapter->tx_ring->crb_cmd_consumer);
	}

	regs_buff[i++] = NXRDIO(adapter, adapter->tx_ring->crb_cmd_producer);

	regs_buff[i++] = NXRDIO(adapter,
			 recv_ctx->rds_rings[0].crb_rcv_producer);
	regs_buff[i++] = NXRDIO(adapter,
			 recv_ctx->rds_rings[1].crb_rcv_producer);

	regs_buff[i++] = adapter->max_sds_rings;

	for (ring = 0; ring < adapter->max_sds_rings; ring++) {
		sds_ring = &(recv_ctx->sds_rings[ring]);
		regs_buff[i++] = NXRDIO(adapter,
					sds_ring->crb_sts_consumer);
	}
}