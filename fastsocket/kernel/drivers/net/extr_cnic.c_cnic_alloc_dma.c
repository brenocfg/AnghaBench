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
struct cnic_local {int /*<<< orphan*/  (* setup_pgtbl ) (struct cnic_dev*,struct cnic_dma*) ;} ;
struct cnic_dma {int num_pages; int pgtbl_size; int /*<<< orphan*/ * pgtbl; int /*<<< orphan*/  pgtbl_map; int /*<<< orphan*/ ** pg_arr; int /*<<< orphan*/ * pg_map_arr; } ;
struct cnic_dev {TYPE_1__* pcidev; struct cnic_local* cnic_priv; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2_PAGE_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cnic_free_dma (struct cnic_dev*,struct cnic_dma*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cnic_dev*,struct cnic_dma*) ; 

__attribute__((used)) static int cnic_alloc_dma(struct cnic_dev *dev, struct cnic_dma *dma,
			  int pages, int use_pg_tbl)
{
	int i, size;
	struct cnic_local *cp = dev->cnic_priv;

	size = pages * (sizeof(void *) + sizeof(dma_addr_t));
	dma->pg_arr = kzalloc(size, GFP_ATOMIC);
	if (dma->pg_arr == NULL)
		return -ENOMEM;

	dma->pg_map_arr = (dma_addr_t *) (dma->pg_arr + pages);
	dma->num_pages = pages;

	for (i = 0; i < pages; i++) {
		dma->pg_arr[i] = dma_alloc_coherent(&dev->pcidev->dev,
						    BNX2_PAGE_SIZE,
						    &dma->pg_map_arr[i],
						    GFP_ATOMIC);
		if (dma->pg_arr[i] == NULL)
			goto error;
	}
	if (!use_pg_tbl)
		return 0;

	dma->pgtbl_size = ((pages * 8) + BNX2_PAGE_SIZE - 1) &
			  ~(BNX2_PAGE_SIZE - 1);
	dma->pgtbl = dma_alloc_coherent(&dev->pcidev->dev, dma->pgtbl_size,
					&dma->pgtbl_map, GFP_ATOMIC);
	if (dma->pgtbl == NULL)
		goto error;

	cp->setup_pgtbl(dev, dma);

	return 0;

error:
	cnic_free_dma(dev, dma);
	return -ENOMEM;
}