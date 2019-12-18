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
struct TYPE_6__ {TYPE_1__* ring; } ;
struct TYPE_8__ {TYPE_3__* ring; } ;
struct igb_q_vector {int /*<<< orphan*/  napi; TYPE_2__ rx; TYPE_4__ tx; } ;
struct igb_adapter {struct igb_q_vector** q_vector; int /*<<< orphan*/ ** tx_ring; } ;
struct TYPE_7__ {size_t queue_index; } ;
struct TYPE_5__ {size_t queue_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct igb_q_vector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void igb_free_q_vector(struct igb_adapter *adapter, int v_idx)
{
	struct igb_q_vector *q_vector = adapter->q_vector[v_idx];

	if (q_vector->tx.ring)
		adapter->tx_ring[q_vector->tx.ring->queue_index] = NULL;

	if (q_vector->rx.ring)
		adapter->tx_ring[q_vector->rx.ring->queue_index] = NULL;

	adapter->q_vector[v_idx] = NULL;
	netif_napi_del(&q_vector->napi);

	/* igb_get_stats64() might access the rings on this vector,
	 * we must wait a grace period before freeing it.
	 */
	kfree_rcu(q_vector, rcu);
}