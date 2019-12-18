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
struct efx_tx_queue {int queue; } ;

/* Variables and functions */
 int EFX_TXQ_TYPE_OFFLOAD ; 

__attribute__((used)) static struct efx_tx_queue *efx_tx_queue_partner(struct efx_tx_queue *tx_queue)
{
	if (tx_queue->queue & EFX_TXQ_TYPE_OFFLOAD)
		return tx_queue - EFX_TXQ_TYPE_OFFLOAD;
	else
		return tx_queue + EFX_TXQ_TYPE_OFFLOAD;
}