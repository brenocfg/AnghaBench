#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct ehca_shca {int /*<<< orphan*/  ib_device; TYPE_4__ ipz_hca_handle; } ;
struct ehca_pd {int dummy; } ;
struct ehca_mr_pginfo {scalar_t__ num_hwpages; int /*<<< orphan*/  num_kpages; } ;
struct TYPE_6__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_7__ {TYPE_2__ ib_mr; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
struct ehca_mr {scalar_t__ num_hwpages; int flags; int /*<<< orphan*/  fmr_map_cnt; int /*<<< orphan*/  fmr_max_maps; int /*<<< orphan*/  fmr_max_pages; int /*<<< orphan*/  fmr_page_size; int /*<<< orphan*/  hwpage_size; TYPE_3__ ib; TYPE_1__ ipz_mr_handle; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EHCA_MR_FLAG_MAXMR ; 
 int /*<<< orphan*/  EHCA_REG_MR ; 
 scalar_t__ H_SUCCESS ; 
 scalar_t__ MAX_RPAGES ; 
 int ehca2ib_return_code (scalar_t__) ; 
 int /*<<< orphan*/  ehca_dbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ehca_mr_deletenew (struct ehca_mr*) ; 
 int ehca_reg_mr (struct ehca_shca*,struct ehca_mr*,scalar_t__*,scalar_t__,int,struct ehca_pd*,struct ehca_mr_pginfo*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int ehca_rereg_mr_rereg1 (struct ehca_shca*,struct ehca_mr*,scalar_t__*,scalar_t__,int,struct ehca_pd*,struct ehca_mr_pginfo*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ hipz_h_free_resource_mr (TYPE_4__,struct ehca_mr*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 

int ehca_rereg_mr(struct ehca_shca *shca,
		  struct ehca_mr *e_mr,
		  u64 *iova_start,
		  u64 size,
		  int acl,
		  struct ehca_pd *e_pd,
		  struct ehca_mr_pginfo *pginfo,
		  u32 *lkey,
		  u32 *rkey)
{
	int ret = 0;
	u64 h_ret;
	int rereg_1_hcall = 1; /* 1: use hipz_h_reregister_pmr directly */
	int rereg_3_hcall = 0; /* 1: use 3 hipz calls for reregistration */

	/* first determine reregistration hCall(s) */
	if ((pginfo->num_hwpages > MAX_RPAGES) ||
	    (e_mr->num_hwpages > MAX_RPAGES) ||
	    (pginfo->num_hwpages > e_mr->num_hwpages)) {
		ehca_dbg(&shca->ib_device, "Rereg3 case, "
			 "pginfo->num_hwpages=%llx e_mr->num_hwpages=%x",
			 pginfo->num_hwpages, e_mr->num_hwpages);
		rereg_1_hcall = 0;
		rereg_3_hcall = 1;
	}

	if (e_mr->flags & EHCA_MR_FLAG_MAXMR) {	/* check for max-MR */
		rereg_1_hcall = 0;
		rereg_3_hcall = 1;
		e_mr->flags &= ~EHCA_MR_FLAG_MAXMR;
		ehca_err(&shca->ib_device, "Rereg MR for max-MR! e_mr=%p",
			 e_mr);
	}

	if (rereg_1_hcall) {
		ret = ehca_rereg_mr_rereg1(shca, e_mr, iova_start, size,
					   acl, e_pd, pginfo, lkey, rkey);
		if (ret) {
			if (ret == -EAGAIN)
				rereg_3_hcall = 1;
			else
				goto ehca_rereg_mr_exit0;
		}
	}

	if (rereg_3_hcall) {
		struct ehca_mr save_mr;

		/* first deregister old MR */
		h_ret = hipz_h_free_resource_mr(shca->ipz_hca_handle, e_mr);
		if (h_ret != H_SUCCESS) {
			ehca_err(&shca->ib_device, "hipz_free_mr failed, "
				 "h_ret=%lli e_mr=%p hca_hndl=%llx mr_hndl=%llx "
				 "mr->lkey=%x",
				 h_ret, e_mr, shca->ipz_hca_handle.handle,
				 e_mr->ipz_mr_handle.handle,
				 e_mr->ib.ib_mr.lkey);
			ret = ehca2ib_return_code(h_ret);
			goto ehca_rereg_mr_exit0;
		}
		/* clean ehca_mr_t, without changing struct ib_mr and lock */
		save_mr = *e_mr;
		ehca_mr_deletenew(e_mr);

		/* set some MR values */
		e_mr->flags = save_mr.flags;
		e_mr->hwpage_size = save_mr.hwpage_size;
		e_mr->fmr_page_size = save_mr.fmr_page_size;
		e_mr->fmr_max_pages = save_mr.fmr_max_pages;
		e_mr->fmr_max_maps = save_mr.fmr_max_maps;
		e_mr->fmr_map_cnt = save_mr.fmr_map_cnt;

		ret = ehca_reg_mr(shca, e_mr, iova_start, size, acl,
				  e_pd, pginfo, lkey, rkey, EHCA_REG_MR);
		if (ret) {
			u32 offset = (u64)(&e_mr->flags) - (u64)e_mr;
			memcpy(&e_mr->flags, &(save_mr.flags),
			       sizeof(struct ehca_mr) - offset);
			goto ehca_rereg_mr_exit0;
		}
	}

ehca_rereg_mr_exit0:
	if (ret)
		ehca_err(&shca->ib_device, "ret=%i shca=%p e_mr=%p "
			 "iova_start=%p size=%llx acl=%x e_pd=%p pginfo=%p "
			 "num_kpages=%llx lkey=%x rkey=%x rereg_1_hcall=%x "
			 "rereg_3_hcall=%x", ret, shca, e_mr, iova_start, size,
			 acl, e_pd, pginfo, pginfo->num_kpages, *lkey, *rkey,
			 rereg_1_hcall, rereg_3_hcall);
	return ret;
}