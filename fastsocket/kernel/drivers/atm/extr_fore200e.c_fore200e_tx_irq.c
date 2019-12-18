#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct host_txq_entry {int* status; scalar_t__ incarn; int /*<<< orphan*/  skb; struct fore200e_vc_map* vc_map; TYPE_3__* tpd; int /*<<< orphan*/  data; } ;
struct host_txq {scalar_t__ txing; size_t tail; struct host_txq_entry* host_entry; } ;
struct fore200e_vc_map {scalar_t__ incarn; struct atm_vcc* vcc; } ;
struct fore200e {struct host_txq host_txq; TYPE_4__* atm_dev; TYPE_1__* bus; } ;
struct atm_vcc {TYPE_5__* stats; int /*<<< orphan*/  (* pop ) (struct atm_vcc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  sk_wmem_alloc; } ;
struct TYPE_11__ {int /*<<< orphan*/  tx; int /*<<< orphan*/  tx_err; } ;
struct TYPE_10__ {int /*<<< orphan*/  number; } ;
struct TYPE_9__ {TYPE_2__* tsd; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* dma_unmap ) (struct fore200e*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct atm_vcc*) ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DPRINTK (int,char*,struct host_txq_entry*,...) ; 
 int /*<<< orphan*/  FORE200E_NEXT_ENTRY (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_SIZE_TX ; 
 int STATUS_COMPLETE ; 
 int STATUS_ERROR ; 
 int STATUS_FREE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 TYPE_6__* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  stub1 (struct fore200e*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fore200e_tx_irq(struct fore200e* fore200e)
{
    struct host_txq*        txq = &fore200e->host_txq;
    struct host_txq_entry*  entry;
    struct atm_vcc*         vcc;
    struct fore200e_vc_map* vc_map;

    if (fore200e->host_txq.txing == 0)
	return;

    for (;;) {
	
	entry = &txq->host_entry[ txq->tail ];

        if ((*entry->status & STATUS_COMPLETE) == 0) {
	    break;
	}

	DPRINTK(3, "TX COMPLETED: entry = %p [tail = %d], vc_map = %p, skb = %p\n", 
		entry, txq->tail, entry->vc_map, entry->skb);

	/* free copy of misaligned data */
	kfree(entry->data);
	
	/* remove DMA mapping */
	fore200e->bus->dma_unmap(fore200e, entry->tpd->tsd[ 0 ].buffer, entry->tpd->tsd[ 0 ].length,
				 DMA_TO_DEVICE);

	vc_map = entry->vc_map;

	/* vcc closed since the time the entry was submitted for tx? */
	if ((vc_map->vcc == NULL) ||
	    (test_bit(ATM_VF_READY, &vc_map->vcc->flags) == 0)) {

	    DPRINTK(1, "no ready vcc found for PDU sent on device %d\n",
		    fore200e->atm_dev->number);

	    dev_kfree_skb_any(entry->skb);
	}
	else {
	    ASSERT(vc_map->vcc);

	    /* vcc closed then immediately re-opened? */
	    if (vc_map->incarn != entry->incarn) {

		/* when a vcc is closed, some PDUs may be still pending in the tx queue.
		   if the same vcc is immediately re-opened, those pending PDUs must
		   not be popped after the completion of their emission, as they refer
		   to the prior incarnation of that vcc. otherwise, sk_atm(vcc)->sk_wmem_alloc
		   would be decremented by the size of the (unrelated) skb, possibly
		   leading to a negative sk->sk_wmem_alloc count, ultimately freezing the vcc.
		   we thus bind the tx entry to the current incarnation of the vcc
		   when the entry is submitted for tx. When the tx later completes,
		   if the incarnation number of the tx entry does not match the one
		   of the vcc, then this implies that the vcc has been closed then re-opened.
		   we thus just drop the skb here. */

		DPRINTK(1, "vcc closed-then-re-opened; dropping PDU sent on device %d\n",
			fore200e->atm_dev->number);

		dev_kfree_skb_any(entry->skb);
	    }
	    else {
		vcc = vc_map->vcc;
		ASSERT(vcc);

		/* notify tx completion */
		if (vcc->pop) {
		    vcc->pop(vcc, entry->skb);
		}
		else {
		    dev_kfree_skb_any(entry->skb);
		}
#if 1
		/* race fixed by the above incarnation mechanism, but... */
		if (atomic_read(&sk_atm(vcc)->sk_wmem_alloc) < 0) {
		    atomic_set(&sk_atm(vcc)->sk_wmem_alloc, 0);
		}
#endif
		/* check error condition */
		if (*entry->status & STATUS_ERROR)
		    atomic_inc(&vcc->stats->tx_err);
		else
		    atomic_inc(&vcc->stats->tx);
	    }
	}

	*entry->status = STATUS_FREE;

	fore200e->host_txq.txing--;

	FORE200E_NEXT_ENTRY(txq->tail, QUEUE_SIZE_TX);
    }
}