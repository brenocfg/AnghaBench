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
typedef  size_t u64 ;
typedef  size_t u32 ;
struct rx_ring_info {unsigned int rcr_index; size_t* rbr_sizes; int /*<<< orphan*/  rbr_refill_pending; int /*<<< orphan*/ * rcr; int /*<<< orphan*/  rx_dropped; } ;
struct page {size_t index; int /*<<< orphan*/ * mapping; } ;
struct niu {int /*<<< orphan*/  device; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap_page ) (int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int NEXT_RCR (struct rx_ring_info*,unsigned int) ; 
 size_t PAGE_SIZE ; 
 size_t RCR_ENTRY_MULTI ; 
 size_t RCR_ENTRY_PKTBUFSZ ; 
 size_t RCR_ENTRY_PKTBUFSZ_SHIFT ; 
 size_t RCR_ENTRY_PKT_BUF_ADDR ; 
 size_t RCR_ENTRY_PKT_BUF_ADDR_SHIFT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 size_t le64_to_cpup (int /*<<< orphan*/ *) ; 
 struct page* niu_find_rxpage (struct rx_ring_info*,size_t,struct page***) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_rx_pkt_ignore(struct niu *np, struct rx_ring_info *rp)
{
	unsigned int index = rp->rcr_index;
	int num_rcr = 0;

	rp->rx_dropped++;
	while (1) {
		struct page *page, **link;
		u64 addr, val;
		u32 rcr_size;

		num_rcr++;

		val = le64_to_cpup(&rp->rcr[index]);
		addr = (val & RCR_ENTRY_PKT_BUF_ADDR) <<
			RCR_ENTRY_PKT_BUF_ADDR_SHIFT;
		page = niu_find_rxpage(rp, addr, &link);

		rcr_size = rp->rbr_sizes[(val & RCR_ENTRY_PKTBUFSZ) >>
					 RCR_ENTRY_PKTBUFSZ_SHIFT];
		if ((page->index + PAGE_SIZE) - rcr_size == addr) {
			*link = (struct page *) page->mapping;
			np->ops->unmap_page(np->device, page->index,
					    PAGE_SIZE, DMA_FROM_DEVICE);
			page->index = 0;
			page->mapping = NULL;
			__free_page(page);
			rp->rbr_refill_pending++;
		}

		index = NEXT_RCR(rp, index);
		if (!(val & RCR_ENTRY_MULTI))
			break;

	}
	rp->rcr_index = index;

	return num_rcr;
}