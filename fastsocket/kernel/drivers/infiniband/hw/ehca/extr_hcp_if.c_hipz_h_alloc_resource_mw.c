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
typedef  scalar_t__ u32 ;
struct ipz_pd {int /*<<< orphan*/  value; } ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {unsigned long handle; } ;
struct ehca_mw_hipzout_parms {scalar_t__ rkey; TYPE_1__ handle; } ;
struct ehca_mw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_ALLOC_RESOURCE ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  ehca_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_alloc_resource_mw(const struct ipz_adapter_handle adapter_handle,
			     const struct ehca_mw *mw,
			     const struct ipz_pd pd,
			     struct ehca_mw_hipzout_parms *outparms)
{
	u64 ret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	ret = ehca_plpar_hcall9(H_ALLOC_RESOURCE, outs,
				adapter_handle.handle,      /* r4 */
				6,                          /* r5 */
				pd.value,                   /* r6 */
				0, 0, 0, 0, 0, 0);
	outparms->handle.handle = outs[0];
	outparms->rkey = (u32)outs[3];

	return ret;
}