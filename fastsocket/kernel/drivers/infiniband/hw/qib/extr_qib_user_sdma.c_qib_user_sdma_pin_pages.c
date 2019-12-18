#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qib_user_sdma_pkt {int /*<<< orphan*/  naddr; } ;
struct qib_devdata {TYPE_1__* pcidev; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 unsigned long PAGE_MASK ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_user_pages (TYPE_2__*,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ,int,struct page**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  qib_user_sdma_init_frag (struct qib_user_sdma_pkt*,int /*<<< orphan*/ ,unsigned long,int const,int,int,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qib_user_sdma_page_length (unsigned long,int) ; 

__attribute__((used)) static int qib_user_sdma_pin_pages(const struct qib_devdata *dd,
				   struct qib_user_sdma_pkt *pkt,
				   unsigned long addr, int tlen, int npages)
{
	struct page *pages[2];
	int j;
	int ret;

	ret = get_user_pages(current, current->mm, addr,
			     npages, 0, 1, pages, NULL);

	if (ret != npages) {
		int i;

		for (i = 0; i < ret; i++)
			put_page(pages[i]);

		ret = -ENOMEM;
		goto done;
	}

	for (j = 0; j < npages; j++) {
		/* map the pages... */
		const int flen = qib_user_sdma_page_length(addr, tlen);
		dma_addr_t dma_addr =
			dma_map_page(&dd->pcidev->dev,
				     pages[j], 0, flen, DMA_TO_DEVICE);
		unsigned long fofs = addr & ~PAGE_MASK;

		if (dma_mapping_error(&dd->pcidev->dev, dma_addr)) {
			ret = -ENOMEM;
			goto done;
		}

		qib_user_sdma_init_frag(pkt, pkt->naddr, fofs, flen, 1, 1,
					pages[j], kmap(pages[j]), dma_addr);

		pkt->naddr++;
		addr += flen;
		tlen -= flen;
	}

done:
	return ret;
}