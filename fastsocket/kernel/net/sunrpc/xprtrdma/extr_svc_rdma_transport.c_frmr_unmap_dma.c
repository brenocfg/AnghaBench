#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svcxprt_rdma {int /*<<< orphan*/  sc_dma_used; } ;
struct svc_rdma_fastreg_mr {int page_list_len; int /*<<< orphan*/  direction; TYPE_2__* mr; TYPE_1__* page_list; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/ * page_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void frmr_unmap_dma(struct svcxprt_rdma *xprt,
			   struct svc_rdma_fastreg_mr *frmr)
{
	int page_no;
	for (page_no = 0; page_no < frmr->page_list_len; page_no++) {
		dma_addr_t addr = frmr->page_list->page_list[page_no];
		if (ib_dma_mapping_error(frmr->mr->device, addr))
			continue;
		atomic_dec(&xprt->sc_dma_used);
		ib_dma_unmap_page(frmr->mr->device, addr, PAGE_SIZE,
				  frmr->direction);
	}
}