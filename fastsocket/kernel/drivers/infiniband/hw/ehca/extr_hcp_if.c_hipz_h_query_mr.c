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
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u32 ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct ehca_mr_hipzout_parms {unsigned long len; unsigned long vaddr; unsigned long acl; void* rkey; void* lkey; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
struct ehca_mr {TYPE_1__ ipz_mr_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_QUERY_MR ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  ehca_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_query_mr(const struct ipz_adapter_handle adapter_handle,
		    const struct ehca_mr *mr,
		    struct ehca_mr_hipzout_parms *outparms)
{
	u64 ret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	ret = ehca_plpar_hcall9(H_QUERY_MR, outs,
				adapter_handle.handle,     /* r4 */
				mr->ipz_mr_handle.handle,  /* r5 */
				0, 0, 0, 0, 0, 0, 0);
	outparms->len = outs[0];
	outparms->vaddr = outs[1];
	outparms->acl  = outs[4] >> 32;
	outparms->lkey = (u32)(outs[5] >> 32);
	outparms->rkey = (u32)(outs[5] & (0xffffffff));

	return ret;
}