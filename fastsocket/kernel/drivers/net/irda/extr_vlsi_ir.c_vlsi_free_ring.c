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
struct vlsi_ring {unsigned int size; int /*<<< orphan*/  dir; int /*<<< orphan*/  len; int /*<<< orphan*/  pdev; struct ring_descr* rd; } ;
struct ring_descr {struct vlsi_ring* buf; scalar_t__ skb; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct vlsi_ring*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rd_get_addr (struct ring_descr*) ; 
 int /*<<< orphan*/  rd_set_addr_status (struct ring_descr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlsi_free_ring(struct vlsi_ring *r)
{
	struct ring_descr *rd;
	unsigned	i;
	dma_addr_t	busaddr;

	for (i = 0; i < r->size; i++) {
		rd = r->rd + i;
		if (rd->skb)
			dev_kfree_skb_any(rd->skb);
		busaddr = rd_get_addr(rd);
		rd_set_addr_status(rd, 0, 0);
		if (busaddr)
			pci_unmap_single(r->pdev, busaddr, r->len, r->dir);
		kfree(rd->buf);
	}
	kfree(r);
	return 0;
}