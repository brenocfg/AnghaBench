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
struct efx_tx_queue {int /*<<< orphan*/  channel; int /*<<< orphan*/  flush_outstanding; } ;
struct efx_nic {int n_tx_channels; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_CHANNEL_MAGIC_TX_DRAIN (struct efx_tx_queue*) ; 
 int EFX_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EFX_TXQ_TYPES ; 
 int /*<<< orphan*/  FSF_AZ_DRIVER_EV_SUBDATA ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct efx_tx_queue* efx_get_tx_queue (struct efx_nic*,int,int) ; 
 int /*<<< orphan*/  efx_magic_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
efx_handle_tx_flush_done(struct efx_nic *efx, efx_qword_t *event)
{
	struct efx_tx_queue *tx_queue;
	int qid;

	qid = EFX_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_SUBDATA);
	if (qid < EFX_TXQ_TYPES * efx->n_tx_channels) {
		tx_queue = efx_get_tx_queue(efx, qid / EFX_TXQ_TYPES,
					    qid % EFX_TXQ_TYPES);
		if (atomic_cmpxchg(&tx_queue->flush_outstanding, 1, 0)) {
			efx_magic_event(tx_queue->channel,
					EFX_CHANNEL_MAGIC_TX_DRAIN(tx_queue));
		}
	}
}