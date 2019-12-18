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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ocrdma_ucontext {int dummy; } ;
struct ocrdma_pd {int id; struct ocrdma_ucontext* uctx; scalar_t__ dpp_enabled; TYPE_2__* dev; } ;
struct ocrdma_alloc_pd_uresp {int id; scalar_t__ dpp_page_addr_lo; int /*<<< orphan*/  dpp_page_addr_hi; scalar_t__ dpp_enabled; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
typedef  int /*<<< orphan*/  rsp ;
struct TYPE_3__ {int db_page_size; scalar_t__ dpp_unmapped_addr; scalar_t__ unmapped_db; } ;
struct TYPE_4__ {TYPE_1__ nic_info; } ;

/* Variables and functions */
 int OCRDMA_DPP_PAGE_SIZE ; 
 struct ocrdma_ucontext* get_ocrdma_ucontext (struct ib_ucontext*) ; 
 int ib_copy_to_udata (struct ib_udata*,struct ocrdma_alloc_pd_uresp*,int) ; 
 int /*<<< orphan*/  memset (struct ocrdma_alloc_pd_uresp*,int /*<<< orphan*/ ,int) ; 
 int ocrdma_add_mmap (struct ocrdma_ucontext*,scalar_t__,int) ; 
 int /*<<< orphan*/  ocrdma_del_mmap (struct ocrdma_ucontext*,scalar_t__,int) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int ocrdma_copy_pd_uresp(struct ocrdma_pd *pd,
				struct ib_ucontext *ib_ctx,
				struct ib_udata *udata)
{
	int status;
	u64 db_page_addr;
	u64 dpp_page_addr = 0;
	u32 db_page_size;
	struct ocrdma_alloc_pd_uresp rsp;
	struct ocrdma_ucontext *uctx = get_ocrdma_ucontext(ib_ctx);

	memset(&rsp, 0, sizeof(rsp));
	rsp.id = pd->id;
	rsp.dpp_enabled = pd->dpp_enabled;
	db_page_addr = pd->dev->nic_info.unmapped_db +
			(pd->id * pd->dev->nic_info.db_page_size);
	db_page_size = pd->dev->nic_info.db_page_size;

	status = ocrdma_add_mmap(uctx, db_page_addr, db_page_size);
	if (status)
		return status;

	if (pd->dpp_enabled) {
		dpp_page_addr = pd->dev->nic_info.dpp_unmapped_addr +
				(pd->id * OCRDMA_DPP_PAGE_SIZE);
		status = ocrdma_add_mmap(uctx, dpp_page_addr,
				 OCRDMA_DPP_PAGE_SIZE);
		if (status)
			goto dpp_map_err;
		rsp.dpp_page_addr_hi = upper_32_bits(dpp_page_addr);
		rsp.dpp_page_addr_lo = dpp_page_addr;
	}

	status = ib_copy_to_udata(udata, &rsp, sizeof(rsp));
	if (status)
		goto ucopy_err;

	pd->uctx = uctx;
	return 0;

ucopy_err:
	if (pd->dpp_enabled)
		ocrdma_del_mmap(pd->uctx, dpp_page_addr, OCRDMA_DPP_PAGE_SIZE);
dpp_map_err:
	ocrdma_del_mmap(pd->uctx, db_page_addr, db_page_size);
	return status;
}