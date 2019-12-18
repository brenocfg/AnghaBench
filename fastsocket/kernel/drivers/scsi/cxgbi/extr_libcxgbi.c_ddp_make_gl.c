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
struct scatterlist {unsigned int length; unsigned int offset; } ;
struct pci_dev {int dummy; } ;
struct page {int dummy; } ;
struct cxgbi_gather_list {unsigned int nelem; unsigned int length; unsigned int offset; struct page** pages; int /*<<< orphan*/ * phys_addr; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int CXGBI_DBG_DDP ; 
 unsigned int DDP_THRESHOLD ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ ddp_gl_map (struct pci_dev*,struct cxgbi_gather_list*) ; 
 int /*<<< orphan*/  kfree (struct cxgbi_gather_list*) ; 
 struct cxgbi_gather_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,int,unsigned int,...) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 struct page* sg_page (struct scatterlist*) ; 

__attribute__((used)) static struct cxgbi_gather_list *ddp_make_gl(unsigned int xferlen,
						    struct scatterlist *sgl,
						    unsigned int sgcnt,
						    struct pci_dev *pdev,
						    gfp_t gfp)
{
	struct cxgbi_gather_list *gl;
	struct scatterlist *sg = sgl;
	struct page *sgpage = sg_page(sg);
	unsigned int sglen = sg->length;
	unsigned int sgoffset = sg->offset;
	unsigned int npages = (xferlen + sgoffset + PAGE_SIZE - 1) >>
				PAGE_SHIFT;
	int i = 1, j = 0;

	if (xferlen < DDP_THRESHOLD) {
		log_debug(1 << CXGBI_DBG_DDP,
			"xfer %u < threshold %u, no ddp.\n",
			xferlen, DDP_THRESHOLD);
		return NULL;
	}

	gl = kzalloc(sizeof(struct cxgbi_gather_list) +
		     npages * (sizeof(dma_addr_t) +
		     sizeof(struct page *)), gfp);
	if (!gl) {
		log_debug(1 << CXGBI_DBG_DDP,
			"xfer %u, %u pages, OOM.\n", xferlen, npages);
		return NULL;
	}

	 log_debug(1 << CXGBI_DBG_DDP,
		"xfer %u, sgl %u, gl max %u.\n", xferlen, sgcnt, npages);

	gl->pages = (struct page **)&gl->phys_addr[npages];
	gl->nelem = npages;
	gl->length = xferlen;
	gl->offset = sgoffset;
	gl->pages[0] = sgpage;

	for (i = 1, sg = sg_next(sgl), j = 0; i < sgcnt;
		i++, sg = sg_next(sg)) {
		struct page *page = sg_page(sg);

		if (sgpage == page && sg->offset == sgoffset + sglen)
			sglen += sg->length;
		else {
			/*  make sure the sgl is fit for ddp:
			 *  each has the same page size, and
			 *  all of the middle pages are used completely
			 */
			if ((j && sgoffset) || ((i != sgcnt - 1) &&
			    ((sglen + sgoffset) & ~PAGE_MASK))) {
				log_debug(1 << CXGBI_DBG_DDP,
					"page %d/%u, %u + %u.\n",
					i, sgcnt, sgoffset, sglen);
				goto error_out;
			}

			j++;
			if (j == gl->nelem || sg->offset) {
				log_debug(1 << CXGBI_DBG_DDP,
					"page %d/%u, offset %u.\n",
					j, gl->nelem, sg->offset);
				goto error_out;
			}
			gl->pages[j] = page;
			sglen = sg->length;
			sgoffset = sg->offset;
			sgpage = page;
		}
	}
	gl->nelem = ++j;

	if (ddp_gl_map(pdev, gl) < 0)
		goto error_out;

	return gl;

error_out:
	kfree(gl);
	return NULL;
}