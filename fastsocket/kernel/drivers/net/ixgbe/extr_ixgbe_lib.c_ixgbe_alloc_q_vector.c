#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ixgbe_ring_feature {int offset; int indices; } ;
struct ixgbe_ring {int queue_index; int /*<<< orphan*/  count; int /*<<< orphan*/  state; struct ixgbe_q_vector* q_vector; TYPE_4__* netdev; int /*<<< orphan*/ * dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  work_limit; } ;
struct ixgbe_q_vector {int numa_node; int cpu; int v_idx; int itr; TYPE_5__ rx; TYPE_5__ tx; struct ixgbe_ring* ring; struct ixgbe_adapter* adapter; int /*<<< orphan*/  napi; int /*<<< orphan*/  affinity_mask; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_8__ {TYPE_2__ mac; } ;
struct ixgbe_adapter {int flags; int tx_itr_setting; int rx_itr_setting; struct ixgbe_ring** rx_ring; int /*<<< orphan*/  rx_ring_count; struct ixgbe_ring_feature* ring_feature; TYPE_4__* netdev; TYPE_3__ hw; TYPE_1__* pdev; struct ixgbe_ring** tx_ring; int /*<<< orphan*/  tx_ring_count; int /*<<< orphan*/  tx_work_limit; struct ixgbe_q_vector** q_vector; } ;
struct TYPE_9__ {int features; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IXGBE_10K_ITR ; 
 int IXGBE_20K_ITR ; 
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 int NETIF_F_FCOE_MTU ; 
 size_t RING_F_FCOE ; 
 int /*<<< orphan*/  __IXGBE_RX_CSUM_UDP_ZERO_ERR ; 
 int /*<<< orphan*/  __IXGBE_RX_FCOE ; 
 scalar_t__ cpu_online (int) ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_add_ring (struct ixgbe_ring*,TYPE_5__*) ; 
 scalar_t__ ixgbe_mac_82599EB ; 
 int /*<<< orphan*/  ixgbe_poll ; 
 struct ixgbe_q_vector* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ixgbe_q_vector* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_napi_add (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbe_alloc_q_vector(struct ixgbe_adapter *adapter,
				int v_count, int v_idx,
				int txr_count, int txr_idx,
				int rxr_count, int rxr_idx)
{
	struct ixgbe_q_vector *q_vector;
	struct ixgbe_ring *ring;
	int node = -1;
	int cpu = -1;
	int ring_count, size;

	ring_count = txr_count + rxr_count;
	size = sizeof(struct ixgbe_q_vector) +
	       (sizeof(struct ixgbe_ring) * ring_count);

	/* customize cpu for Flow Director mapping */
	if (adapter->flags & IXGBE_FLAG_FDIR_HASH_CAPABLE) {
		if (cpu_online(v_idx)) {
			cpu = v_idx;
			node = cpu_to_node(cpu);
		}
	}

	/* allocate q_vector and rings */
	q_vector = kzalloc_node(size, GFP_KERNEL, node);
	if (!q_vector)
		q_vector = kzalloc(size, GFP_KERNEL);
	if (!q_vector)
		return -ENOMEM;

	/* setup affinity mask and node */
	if (cpu != -1)
		cpumask_set_cpu(cpu, &q_vector->affinity_mask);
	q_vector->numa_node = node;

#ifdef CONFIG_IXGBE_DCA
	/* initialize CPU for DCA */
	q_vector->cpu = -1;

#endif
	/* initialize NAPI */
	netif_napi_add(adapter->netdev, &q_vector->napi,
		       ixgbe_poll, 64);

	/* tie q_vector and adapter together */
	adapter->q_vector[v_idx] = q_vector;
	q_vector->adapter = adapter;
	q_vector->v_idx = v_idx;

	/* initialize work limits */
	q_vector->tx.work_limit = adapter->tx_work_limit;

	/* initialize pointer to rings */
	ring = q_vector->ring;

	/* intialize ITR */
	if (txr_count && !rxr_count) {
		/* tx only vector */
		if (adapter->tx_itr_setting == 1)
			q_vector->itr = IXGBE_10K_ITR;
		else
			q_vector->itr = adapter->tx_itr_setting;
	} else {
		/* rx or rx/tx vector */
		if (adapter->rx_itr_setting == 1)
			q_vector->itr = IXGBE_20K_ITR;
		else
			q_vector->itr = adapter->rx_itr_setting;
	}

	while (txr_count) {
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Tx values */
		ixgbe_add_ring(ring, &q_vector->tx);

		/* apply Tx specific ring traits */
		ring->count = adapter->tx_ring_count;
		ring->queue_index = txr_idx;

		/* assign ring to adapter */
		adapter->tx_ring[txr_idx] = ring;

		/* update count and index */
		txr_count--;
		txr_idx += v_count;

		/* push pointer to next ring */
		ring++;
	}

	while (rxr_count) {
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Rx values */
		ixgbe_add_ring(ring, &q_vector->rx);

		/*
		 * 82599 errata, UDP frames with a 0 checksum
		 * can be marked as checksum errors.
		 */
		if (adapter->hw.mac.type == ixgbe_mac_82599EB)
			set_bit(__IXGBE_RX_CSUM_UDP_ZERO_ERR, &ring->state);

#ifdef IXGBE_FCOE
		if (adapter->netdev->features & NETIF_F_FCOE_MTU) {
			struct ixgbe_ring_feature *f;
			f = &adapter->ring_feature[RING_F_FCOE];
			if ((rxr_idx >= f->offset) &&
			    (rxr_idx < f->offset + f->indices))
				set_bit(__IXGBE_RX_FCOE, &ring->state);
		}

#endif /* IXGBE_FCOE */
		/* apply Rx specific ring traits */
		ring->count = adapter->rx_ring_count;
		ring->queue_index = rxr_idx;

		/* assign ring to adapter */
		adapter->rx_ring[rxr_idx] = ring;

		/* update count and index */
		rxr_count--;
		rxr_idx += v_count;

		/* push pointer to next ring */
		ring++;
	}

	return 0;
}