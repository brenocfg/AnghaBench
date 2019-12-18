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
typedef  unsigned long long u64 ;
typedef  void* u32 ;
struct ipz_pd {int /*<<< orphan*/  value; } ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {unsigned long handle; } ;
struct ehca_mr_hipzout_parms {void* rkey; void* lkey; TYPE_2__ handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct ehca_mr {TYPE_1__ ipz_mr_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_REGISTER_SMR ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 unsigned long long ehca_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long const,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_register_smr(const struct ipz_adapter_handle adapter_handle,
			const struct ehca_mr *mr,
			const struct ehca_mr *orig_mr,
			const u64 vaddr_in,
			const u32 access_ctrl,
			const struct ipz_pd pd,
			struct ehca_mr_hipzout_parms *outparms)
{
	u64 ret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	ret = ehca_plpar_hcall9(H_REGISTER_SMR, outs,
				adapter_handle.handle,            /* r4 */
				orig_mr->ipz_mr_handle.handle,    /* r5 */
				vaddr_in,                         /* r6 */
				(((u64)access_ctrl) << 32ULL),    /* r7 */
				pd.value,                         /* r8 */
				0, 0, 0, 0);
	outparms->handle.handle = outs[0];
	outparms->lkey = (u32)outs[2];
	outparms->rkey = (u32)outs[3];

	return ret;
}