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
struct efx_tx_queue {int queue; TYPE_1__* efx; } ;
struct TYPE_2__ {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EFX_TXQ_TYPE_HIGHPRI ; 
 int netdev_get_num_tc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool efx_tx_queue_used(struct efx_tx_queue *tx_queue)
{
	return !(netdev_get_num_tc(tx_queue->efx->net_dev) < 2 &&
		 tx_queue->queue & EFX_TXQ_TYPE_HIGHPRI);
}