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
struct srp_target_port {TYPE_1__** tx_ring; int /*<<< orphan*/  srp_host; TYPE_1__** rx_ring; int /*<<< orphan*/  free_tx; int /*<<< orphan*/  max_iu_len; int /*<<< orphan*/  max_ti_iu_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SRP_RQ_SIZE ; 
 int SRP_SQ_SIZE ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* srp_alloc_iu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_free_iu (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int srp_alloc_iu_bufs(struct srp_target_port *target)
{
	int i;

	for (i = 0; i < SRP_RQ_SIZE; ++i) {
		target->rx_ring[i] = srp_alloc_iu(target->srp_host,
						  target->max_ti_iu_len,
						  GFP_KERNEL, DMA_FROM_DEVICE);
		if (!target->rx_ring[i])
			goto err;
	}

	for (i = 0; i < SRP_SQ_SIZE; ++i) {
		target->tx_ring[i] = srp_alloc_iu(target->srp_host,
						  target->max_iu_len,
						  GFP_KERNEL, DMA_TO_DEVICE);
		if (!target->tx_ring[i])
			goto err;

		list_add(&target->tx_ring[i]->list, &target->free_tx);
	}

	return 0;

err:
	for (i = 0; i < SRP_RQ_SIZE; ++i) {
		srp_free_iu(target->srp_host, target->rx_ring[i]);
		target->rx_ring[i] = NULL;
	}

	for (i = 0; i < SRP_SQ_SIZE; ++i) {
		srp_free_iu(target->srp_host, target->tx_ring[i]);
		target->tx_ring[i] = NULL;
	}

	return -ENOMEM;
}