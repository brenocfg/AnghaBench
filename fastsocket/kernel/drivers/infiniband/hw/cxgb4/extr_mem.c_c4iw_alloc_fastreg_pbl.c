#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ib_fast_reg_page_list {int max_page_list_len; int /*<<< orphan*/ * page_list; } ;
struct ib_device {int dummy; } ;
struct c4iw_fr_page_list {int size; struct ib_fast_reg_page_list ibpl; struct c4iw_dev* dev; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_6__ {TYPE_2__ lldi; } ;
struct c4iw_dev {TYPE_3__ rdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_fast_reg_page_list* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct c4iw_fr_page_list* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_addr_set (struct c4iw_fr_page_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct c4iw_dev* to_c4iw_dev (struct ib_device*) ; 

struct ib_fast_reg_page_list *c4iw_alloc_fastreg_pbl(struct ib_device *device,
						     int page_list_len)
{
	struct c4iw_fr_page_list *c4pl;
	struct c4iw_dev *dev = to_c4iw_dev(device);
	dma_addr_t dma_addr;
	int size = sizeof *c4pl + page_list_len * sizeof(u64);

	c4pl = dma_alloc_coherent(&dev->rdev.lldi.pdev->dev, size,
				  &dma_addr, GFP_KERNEL);
	if (!c4pl)
		return ERR_PTR(-ENOMEM);

	pci_unmap_addr_set(c4pl, mapping, dma_addr);
	c4pl->dma_addr = dma_addr;
	c4pl->dev = dev;
	c4pl->size = size;
	c4pl->ibpl.page_list = (u64 *)(c4pl + 1);
	c4pl->ibpl.max_page_list_len = page_list_len;

	return &c4pl->ibpl;
}