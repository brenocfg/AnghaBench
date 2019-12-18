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
typedef  scalar_t__ u64 ;
struct ocrdma_pd {int id; scalar_t__ uctx; scalar_t__ dpp_enabled; struct ocrdma_dev* dev; } ;
struct TYPE_2__ {int db_page_size; scalar_t__ unmapped_db; scalar_t__ dpp_unmapped_addr; } ;
struct ocrdma_dev {TYPE_1__ nic_info; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int OCRDMA_DPP_PAGE_SIZE ; 
 struct ocrdma_pd* get_ocrdma_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_pd*) ; 
 int /*<<< orphan*/  ocrdma_del_mmap (scalar_t__,scalar_t__,int) ; 
 int ocrdma_mbx_dealloc_pd (struct ocrdma_dev*,struct ocrdma_pd*) ; 

int ocrdma_dealloc_pd(struct ib_pd *ibpd)
{
	struct ocrdma_pd *pd = get_ocrdma_pd(ibpd);
	struct ocrdma_dev *dev = pd->dev;
	int status;
	u64 usr_db;

	status = ocrdma_mbx_dealloc_pd(dev, pd);
	if (pd->uctx) {
		u64 dpp_db = dev->nic_info.dpp_unmapped_addr +
		    (pd->id * OCRDMA_DPP_PAGE_SIZE);
		if (pd->dpp_enabled)
			ocrdma_del_mmap(pd->uctx, dpp_db, OCRDMA_DPP_PAGE_SIZE);
		usr_db = dev->nic_info.unmapped_db +
		    (pd->id * dev->nic_info.db_page_size);
		ocrdma_del_mmap(pd->uctx, usr_db, dev->nic_info.db_page_size);
	}
	kfree(pd);
	return status;
}