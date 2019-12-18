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
typedef  int u8 ;
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct ixgbe_ring_feature {int /*<<< orphan*/  mask; } ;
struct ixgbe_adapter {TYPE_1__* vfinfo; int /*<<< orphan*/  default_up; struct ixgbe_ring_feature* ring_feature; struct net_device* netdev; } ;
struct TYPE_2__ {int vf_api; scalar_t__ pf_qos; scalar_t__ pf_vlan; } ;

/* Variables and functions */
 size_t IXGBE_VF_DEF_QUEUE ; 
 size_t IXGBE_VF_RX_QUEUES ; 
 size_t IXGBE_VF_TRANS_VLAN ; 
 size_t IXGBE_VF_TX_QUEUES ; 
 size_t RING_F_VMDQ ; 
 size_t __ALIGN_MASK (int,int /*<<< orphan*/ ) ; 
#define  ixgbe_mbox_api_11 129 
#define  ixgbe_mbox_api_20 128 
 int netdev_get_num_tc (struct net_device*) ; 
 unsigned int netdev_get_prio_tc_map (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_get_vf_queues(struct ixgbe_adapter *adapter,
			       u32 *msgbuf, u32 vf)
{
	struct net_device *dev = adapter->netdev;
	struct ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	unsigned int default_tc = 0;
	u8 num_tcs = netdev_get_num_tc(dev);

	/* verify the PF is supporting the correct APIs */
	switch (adapter->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_20:
	case ixgbe_mbox_api_11:
		break;
	default:
		return -1;
	}

	/* only allow 1 Tx queue for bandwidth limiting */
	msgbuf[IXGBE_VF_TX_QUEUES] = __ALIGN_MASK(1, ~vmdq->mask);
	msgbuf[IXGBE_VF_RX_QUEUES] = __ALIGN_MASK(1, ~vmdq->mask);

	/* if TCs > 1 determine which TC belongs to default user priority */
	if (num_tcs > 1)
		default_tc = netdev_get_prio_tc_map(dev, adapter->default_up);

	/* notify VF of need for VLAN tag stripping, and correct queue */
	if (num_tcs)
		msgbuf[IXGBE_VF_TRANS_VLAN] = num_tcs;
	else if (adapter->vfinfo[vf].pf_vlan || adapter->vfinfo[vf].pf_qos)
		msgbuf[IXGBE_VF_TRANS_VLAN] = 1;
	else
		msgbuf[IXGBE_VF_TRANS_VLAN] = 0;

	/* notify VF of default queue */
	msgbuf[IXGBE_VF_DEF_QUEUE] = default_tc;

	return 0;
}