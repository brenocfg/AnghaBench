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
struct sge_fl {size_t cidx; size_t size; int /*<<< orphan*/  avail; struct rx_sw_desc* sdesc; } ;
struct rx_sw_desc {int /*<<< orphan*/ * page; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buf_addr (struct rx_sw_desc*) ; 
 int /*<<< orphan*/  get_buf_size (struct rx_sw_desc*) ; 
 scalar_t__ is_buf_mapped (struct rx_sw_desc*) ; 

__attribute__((used)) static void unmap_rx_buf(struct adapter *adap, struct sge_fl *q)
{
	struct rx_sw_desc *d = &q->sdesc[q->cidx];

	if (is_buf_mapped(d))
		dma_unmap_page(adap->pdev_dev, get_buf_addr(d),
			       get_buf_size(d), PCI_DMA_FROMDEVICE);
	d->page = NULL;
	if (++q->cidx == q->size)
		q->cidx = 0;
	q->avail--;
}