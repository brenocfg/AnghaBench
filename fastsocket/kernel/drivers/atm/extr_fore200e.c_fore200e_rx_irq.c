#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct host_rxq_entry {int* status; TYPE_5__* cp_entry; int /*<<< orphan*/  rpd_dma; TYPE_6__* rpd; } ;
struct host_rxq {size_t head; struct host_rxq_entry* host_entry; } ;
struct fore200e_vc_map {struct atm_vcc* vcc; } ;
struct fore200e {TYPE_4__* bus; TYPE_1__* atm_dev; struct host_rxq host_rxq; } ;
struct atm_vcc {TYPE_3__* stats; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; } ;
struct TYPE_13__ {TYPE_2__ atm_header; } ;
struct TYPE_12__ {int /*<<< orphan*/  rpd_haddr; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  rx_err; } ;
struct TYPE_8__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct atm_vcc*) ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  DPRINTK (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORE200E_NEXT_ENTRY (size_t,int /*<<< orphan*/ ) ; 
 struct fore200e_vc_map* FORE200E_VC_MAP (struct fore200e*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_SIZE_RX ; 
 int STATUS_COMPLETE ; 
 int STATUS_ERROR ; 
 int STATUS_FREE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fore200e_collect_rpd (struct fore200e*,TYPE_6__*) ; 
 int /*<<< orphan*/  fore200e_push_rpd (struct fore200e*,struct atm_vcc*,TYPE_6__*) ; 
 int /*<<< orphan*/  fore200e_supply (struct fore200e*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fore200e_rx_irq(struct fore200e* fore200e)
{
    struct host_rxq*        rxq = &fore200e->host_rxq;
    struct host_rxq_entry*  entry;
    struct atm_vcc*         vcc;
    struct fore200e_vc_map* vc_map;

    for (;;) {
	
	entry = &rxq->host_entry[ rxq->head ];

	/* no more received PDUs */
	if ((*entry->status & STATUS_COMPLETE) == 0)
	    break;

	vc_map = FORE200E_VC_MAP(fore200e, entry->rpd->atm_header.vpi, entry->rpd->atm_header.vci);

	if ((vc_map->vcc == NULL) ||
	    (test_bit(ATM_VF_READY, &vc_map->vcc->flags) == 0)) {

	    DPRINTK(1, "no ready VC found for PDU received on %d.%d.%d\n",
		    fore200e->atm_dev->number,
		    entry->rpd->atm_header.vpi, entry->rpd->atm_header.vci);
	}
	else {
	    vcc = vc_map->vcc;
	    ASSERT(vcc);

	    if ((*entry->status & STATUS_ERROR) == 0) {

		fore200e_push_rpd(fore200e, vcc, entry->rpd);
	    }
	    else {
		DPRINTK(2, "damaged PDU on %d.%d.%d\n",
			fore200e->atm_dev->number,
			entry->rpd->atm_header.vpi, entry->rpd->atm_header.vci);
		atomic_inc(&vcc->stats->rx_err);
	    }
	}

	FORE200E_NEXT_ENTRY(rxq->head, QUEUE_SIZE_RX);

	fore200e_collect_rpd(fore200e, entry->rpd);

	/* rewrite the rpd address to ack the received PDU */
	fore200e->bus->write(entry->rpd_dma, &entry->cp_entry->rpd_haddr);
	*entry->status = STATUS_FREE;

	fore200e_supply(fore200e);
    }
}