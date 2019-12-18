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
struct page {int dummy; } ;
struct ipath_user_sdma_pkt {int naddr; } ;
struct ipath_devdata {TYPE_1__* pcidev; } ;
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int copy_from_user (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_user_sdma_init_frag (struct ipath_user_sdma_pkt*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,struct page*,void*,int /*<<< orphan*/ ) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 

__attribute__((used)) static int ipath_user_sdma_coalesce(const struct ipath_devdata *dd,
				    struct ipath_user_sdma_pkt *pkt,
				    const struct iovec *iov,
				    unsigned long niov) {
	int ret = 0;
	struct page *page = alloc_page(GFP_KERNEL);
	void *mpage_save;
	char *mpage;
	int i;
	int len = 0;
	dma_addr_t dma_addr;

	if (!page) {
		ret = -ENOMEM;
		goto done;
	}

	mpage = kmap(page);
	mpage_save = mpage;
	for (i = 0; i < niov; i++) {
		int cfur;

		cfur = copy_from_user(mpage,
				      iov[i].iov_base, iov[i].iov_len);
		if (cfur) {
			ret = -EFAULT;
			goto free_unmap;
		}

		mpage += iov[i].iov_len;
		len += iov[i].iov_len;
	}

	dma_addr = dma_map_page(&dd->pcidev->dev, page, 0, len,
				DMA_TO_DEVICE);
	if (dma_mapping_error(&dd->pcidev->dev, dma_addr)) {
		ret = -ENOMEM;
		goto free_unmap;
	}

	ipath_user_sdma_init_frag(pkt, 1, 0, len, 0, 1, page, mpage_save,
				  dma_addr);
	pkt->naddr = 2;

	goto done;

free_unmap:
	kunmap(page);
	__free_page(page);
done:
	return ret;
}