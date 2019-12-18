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
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u32 ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {unsigned long handle; } ;
struct ehca_cq {TYPE_2__ ipz_cq_handle; int /*<<< orphan*/  galpas; int /*<<< orphan*/  token; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct ehca_alloc_cq_parms {void* act_pages; void* act_nr_of_entries; int /*<<< orphan*/  nr_cqe; TYPE_1__ eq_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_ALLOC_RESOURCE ; 
 int /*<<< orphan*/  H_FREE_RESOURCE ; 
 int /*<<< orphan*/  H_NOT_ENOUGH_RESOURCES ; 
 int /*<<< orphan*/  H_NO_MEM ; 
 int /*<<< orphan*/  H_SUCCESS ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int,...) ; 
 int /*<<< orphan*/  ehca_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hcp_galpas_ctor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

u64 hipz_h_alloc_resource_cq(const struct ipz_adapter_handle adapter_handle,
			     struct ehca_cq *cq,
			     struct ehca_alloc_cq_parms *param)
{
	int rc;
	u64 ret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	ret = ehca_plpar_hcall9(H_ALLOC_RESOURCE, outs,
				adapter_handle.handle,   /* r4  */
				2,	                 /* r5  */
				param->eq_handle.handle, /* r6  */
				cq->token,	         /* r7  */
				param->nr_cqe,           /* r8  */
				0, 0, 0, 0);
	cq->ipz_cq_handle.handle = outs[0];
	param->act_nr_of_entries = (u32)outs[3];
	param->act_pages = (u32)outs[4];

	if (ret == H_SUCCESS) {
		rc = hcp_galpas_ctor(&cq->galpas, 0, outs[5], outs[6]);
		if (rc) {
			ehca_gen_err("Could not establish HW access. rc=%d paddr=%#lx",
				     rc, outs[5]);

			ehca_plpar_hcall_norets(H_FREE_RESOURCE,
						adapter_handle.handle,     /* r4 */
						cq->ipz_cq_handle.handle,  /* r5 */
						0, 0, 0, 0, 0);
			ret = H_NO_MEM;
		}
	}

	if (ret == H_NOT_ENOUGH_RESOURCES)
		ehca_gen_err("Not enough resources. ret=%lli", ret);

	return ret;
}