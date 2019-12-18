#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct ehca_shca {int /*<<< orphan*/  ib_device; TYPE_1__ ipz_hca_handle; } ;
struct ehca_pd {int /*<<< orphan*/  fw_pd; } ;
struct ehca_mr_pginfo {int /*<<< orphan*/  num_hwpages; int /*<<< orphan*/  num_kpages; int /*<<< orphan*/  hwpage_size; } ;
struct ehca_mr_hipzout_parms {int lkey; int rkey; int /*<<< orphan*/  handle; } ;
struct ehca_mr {scalar_t__* start; int acl; scalar_t__ size; int /*<<< orphan*/  hwpage_size; int /*<<< orphan*/  num_hwpages; int /*<<< orphan*/  num_kpages; int /*<<< orphan*/  ipz_mr_handle; } ;
typedef  enum ehca_reg_type { ____Placeholder_ehca_reg_type } ehca_reg_type ;

/* Variables and functions */
 int EHCA_REG_BUSMAP_MR ; 
 int EHCA_REG_MR ; 
 int EINVAL ; 
 scalar_t__ H_SUCCESS ; 
 int ehca2ib_return_code (scalar_t__) ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ehca_mrmw_map_acl (int,int*) ; 
 int /*<<< orphan*/  ehca_mrmw_set_pgsize_hipz_acl (int /*<<< orphan*/ ,int*) ; 
 int ehca_reg_bmap_mr_rpages (struct ehca_shca*,struct ehca_mr*,struct ehca_mr_pginfo*) ; 
 int ehca_reg_mr_rpages (struct ehca_shca*,struct ehca_mr*,struct ehca_mr_pginfo*) ; 
 int ehca_use_hp_mr ; 
 scalar_t__ hipz_h_alloc_resource_mr (TYPE_1__,struct ehca_mr*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,struct ehca_mr_hipzout_parms*) ; 
 scalar_t__ hipz_h_free_resource_mr (TYPE_1__,struct ehca_mr*) ; 

int ehca_reg_mr(struct ehca_shca *shca,
		struct ehca_mr *e_mr,
		u64 *iova_start,
		u64 size,
		int acl,
		struct ehca_pd *e_pd,
		struct ehca_mr_pginfo *pginfo,
		u32 *lkey, /*OUT*/
		u32 *rkey, /*OUT*/
		enum ehca_reg_type reg_type)
{
	int ret;
	u64 h_ret;
	u32 hipz_acl;
	struct ehca_mr_hipzout_parms hipzout;

	ehca_mrmw_map_acl(acl, &hipz_acl);
	ehca_mrmw_set_pgsize_hipz_acl(pginfo->hwpage_size, &hipz_acl);
	if (ehca_use_hp_mr == 1)
		hipz_acl |= 0x00000001;

	h_ret = hipz_h_alloc_resource_mr(shca->ipz_hca_handle, e_mr,
					 (u64)iova_start, size, hipz_acl,
					 e_pd->fw_pd, &hipzout);
	if (h_ret != H_SUCCESS) {
		ehca_err(&shca->ib_device, "hipz_alloc_mr failed, h_ret=%lli "
			 "hca_hndl=%llx", h_ret, shca->ipz_hca_handle.handle);
		ret = ehca2ib_return_code(h_ret);
		goto ehca_reg_mr_exit0;
	}

	e_mr->ipz_mr_handle = hipzout.handle;

	if (reg_type == EHCA_REG_BUSMAP_MR)
		ret = ehca_reg_bmap_mr_rpages(shca, e_mr, pginfo);
	else if (reg_type == EHCA_REG_MR)
		ret = ehca_reg_mr_rpages(shca, e_mr, pginfo);
	else
		ret = -EINVAL;

	if (ret)
		goto ehca_reg_mr_exit1;

	/* successful registration */
	e_mr->num_kpages = pginfo->num_kpages;
	e_mr->num_hwpages = pginfo->num_hwpages;
	e_mr->hwpage_size = pginfo->hwpage_size;
	e_mr->start = iova_start;
	e_mr->size = size;
	e_mr->acl = acl;
	*lkey = hipzout.lkey;
	*rkey = hipzout.rkey;
	return 0;

ehca_reg_mr_exit1:
	h_ret = hipz_h_free_resource_mr(shca->ipz_hca_handle, e_mr);
	if (h_ret != H_SUCCESS) {
		ehca_err(&shca->ib_device, "h_ret=%lli shca=%p e_mr=%p "
			 "iova_start=%p size=%llx acl=%x e_pd=%p lkey=%x "
			 "pginfo=%p num_kpages=%llx num_hwpages=%llx ret=%i",
			 h_ret, shca, e_mr, iova_start, size, acl, e_pd,
			 hipzout.lkey, pginfo, pginfo->num_kpages,
			 pginfo->num_hwpages, ret);
		ehca_err(&shca->ib_device, "internal error in ehca_reg_mr, "
			 "not recoverable");
	}
ehca_reg_mr_exit0:
	if (ret)
		ehca_err(&shca->ib_device, "ret=%i shca=%p e_mr=%p "
			 "iova_start=%p size=%llx acl=%x e_pd=%p pginfo=%p "
			 "num_kpages=%llx num_hwpages=%llx",
			 ret, shca, e_mr, iova_start, size, acl, e_pd, pginfo,
			 pginfo->num_kpages, pginfo->num_hwpages);
	return ret;
}