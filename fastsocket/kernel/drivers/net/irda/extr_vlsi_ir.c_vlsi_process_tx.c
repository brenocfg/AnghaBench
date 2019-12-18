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
typedef  int u16 ;
struct vlsi_ring {int /*<<< orphan*/  dir; int /*<<< orphan*/  len; int /*<<< orphan*/  pdev; } ;
struct ring_descr {TYPE_1__* skb; } ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */
 int RD_TX_UNDRN ; 
 int VLSI_TX_FIFO ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd_get_addr (struct ring_descr*) ; 
 int rd_get_count (struct ring_descr*) ; 
 int rd_get_status (struct ring_descr*) ; 
 int /*<<< orphan*/  rd_set_count (struct ring_descr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd_set_status (struct ring_descr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlsi_process_tx(struct vlsi_ring *r, struct ring_descr *rd)
{
	u16		status;
	int		len;
	int		ret;

	pci_dma_sync_single_for_cpu(r->pdev, rd_get_addr(rd), r->len, r->dir);
	/* dma buffer now owned by the CPU */
	status = rd_get_status(rd);
	if (status & RD_TX_UNDRN)
		ret = VLSI_TX_FIFO;
	else
		ret = 0;
	rd_set_status(rd, 0);

	if (rd->skb) {
		len = rd->skb->len;
		dev_kfree_skb_any(rd->skb);
		rd->skb = NULL;
	}
	else	/* tx-skb already freed? - should never happen */
		len = rd_get_count(rd);		/* incorrect for SIR! (due to wrapping) */

	rd_set_count(rd, 0);
	/* dma buffer still owned by the CPU */

	return (ret) ? -ret : len;
}