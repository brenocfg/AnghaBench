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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cxgbi_gather_list {int nelem; int /*<<< orphan*/ * pages; int /*<<< orphan*/ * phys_addr; } ;

/* Variables and functions */
 int CXGBI_DBG_DDP ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  ddp_gl_unmap (struct pci_dev*,struct cxgbi_gather_list*) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,int,int /*<<< orphan*/ ,struct pci_dev*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ddp_gl_map(struct pci_dev *pdev,
				    struct cxgbi_gather_list *gl)
{
	int i;

	for (i = 0; i < gl->nelem; i++) {
		gl->phys_addr[i] = dma_map_page(&pdev->dev, gl->pages[i], 0,
						PAGE_SIZE,
						PCI_DMA_FROMDEVICE);
		if (unlikely(dma_mapping_error(&pdev->dev, gl->phys_addr[i]))) {
			log_debug(1 << CXGBI_DBG_DDP,
				"page %d 0x%p, 0x%p dma mapping err.\n",
				i, gl->pages[i], pdev);
			goto unmap;
		}
	}
	return i;
unmap:
	if (i) {
		unsigned int nelem = gl->nelem;

		gl->nelem = i;
		ddp_gl_unmap(pdev, gl);
		gl->nelem = nelem;
	}
	return -EINVAL;
}