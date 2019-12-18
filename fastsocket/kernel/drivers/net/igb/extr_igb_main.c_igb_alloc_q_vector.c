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
struct igb_ring {int queue_index; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; struct igb_q_vector* q_vector; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  work_limit; } ;
struct igb_q_vector {int itr_val; TYPE_4__ rx; TYPE_4__ tx; struct igb_ring* ring; scalar_t__ itr_register; struct igb_adapter* adapter; int /*<<< orphan*/  napi; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_7__ {TYPE_2__ mac; scalar_t__ hw_addr; } ;
struct igb_adapter {int rx_itr_setting; int tx_itr_setting; struct igb_ring** rx_ring; int /*<<< orphan*/  rx_ring_count; TYPE_3__ hw; int /*<<< orphan*/  netdev; TYPE_1__* pdev; struct igb_ring** tx_ring; int /*<<< orphan*/  tx_ring_count; int /*<<< orphan*/  tx_work_limit; struct igb_q_vector** q_vector; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ E1000_EITR (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IGB_RING_FLAG_RX_CSUM ; 
 int /*<<< orphan*/  IGB_RING_FLAG_RX_LB_VLAN_BSWAP ; 
 int /*<<< orphan*/  IGB_RING_FLAG_RX_SCTP_CSUM ; 
 int /*<<< orphan*/  IGB_RING_FLAG_TX_CTX_IDX ; 
 int IGB_START_ITR ; 
 scalar_t__ e1000_82575 ; 
 scalar_t__ e1000_82576 ; 
 scalar_t__ e1000_i350 ; 
 int /*<<< orphan*/  igb_add_ring (struct igb_ring*,TYPE_4__*) ; 
 int /*<<< orphan*/  igb_poll ; 
 struct igb_q_vector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int igb_alloc_q_vector(struct igb_adapter *adapter,
			      int v_count, int v_idx,
			      int txr_count, int txr_idx,
			      int rxr_count, int rxr_idx)
{
	struct igb_q_vector *q_vector;
	struct igb_ring *ring;
	int ring_count, size;

	/* igb only supports 1 Tx and/or 1 Rx queue per vector */
	if (txr_count > 1 || rxr_count > 1)
		return -ENOMEM;

	ring_count = txr_count + rxr_count;
	size = sizeof(struct igb_q_vector) +
	       (sizeof(struct igb_ring) * ring_count);

	/* allocate q_vector and rings */
	q_vector = kzalloc(size, GFP_KERNEL);
	if (!q_vector)
		return -ENOMEM;

	/* initialize NAPI */
	netif_napi_add(adapter->netdev, &q_vector->napi,
		       igb_poll, 64);

	/* tie q_vector and adapter together */
	adapter->q_vector[v_idx] = q_vector;
	q_vector->adapter = adapter;

	/* initialize work limits */
	q_vector->tx.work_limit = adapter->tx_work_limit;

	/* initialize ITR configuration */
	q_vector->itr_register = adapter->hw.hw_addr + E1000_EITR(0);
	q_vector->itr_val = IGB_START_ITR;

	/* initialize pointer to rings */
	ring = q_vector->ring;

	/* intialize ITR */
	if (rxr_count) {
		/* rx or rx/tx vector */
		if (!adapter->rx_itr_setting || adapter->rx_itr_setting > 3)
			q_vector->itr_val = adapter->rx_itr_setting;
	} else {
		/* tx only vector */
		if (!adapter->tx_itr_setting || adapter->tx_itr_setting > 3)
			q_vector->itr_val = adapter->tx_itr_setting;
	}

	if (txr_count) {
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Tx values */
		igb_add_ring(ring, &q_vector->tx);

		/* For 82575, context index must be unique per ring. */
		if (adapter->hw.mac.type == e1000_82575)
			set_bit(IGB_RING_FLAG_TX_CTX_IDX, &ring->flags);

		/* apply Tx specific ring traits */
		ring->count = adapter->tx_ring_count;
		ring->queue_index = txr_idx;

		/* assign ring to adapter */
		adapter->tx_ring[txr_idx] = ring;

		/* push pointer to next ring */
		ring++;
	}

	if (rxr_count) {
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Rx values */
		igb_add_ring(ring, &q_vector->rx);

		/* enable rx checksum */
		set_bit(IGB_RING_FLAG_RX_CSUM, &ring->flags);

		/* set flag indicating ring supports SCTP checksum offload */
		if (adapter->hw.mac.type >= e1000_82576)
			set_bit(IGB_RING_FLAG_RX_SCTP_CSUM, &ring->flags);

		/*
		 * On i350, i354, i210, and i211, loopback VLAN packets
		 * have the tag byte-swapped.
		 */
		if (adapter->hw.mac.type >= e1000_i350)
			set_bit(IGB_RING_FLAG_RX_LB_VLAN_BSWAP, &ring->flags);

		/* apply Rx specific ring traits */
		ring->count = adapter->rx_ring_count;
		ring->queue_index = rxr_idx;

		/* assign ring to adapter */
		adapter->rx_ring[rxr_idx] = ring;
	}

	return 0;
}