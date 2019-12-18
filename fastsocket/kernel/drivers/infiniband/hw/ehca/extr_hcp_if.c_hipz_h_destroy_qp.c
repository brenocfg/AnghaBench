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
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
struct ehca_qp {TYPE_1__ ipz_qp_handle; int /*<<< orphan*/  galpas; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_DISABLE_AND_GETC ; 
 int /*<<< orphan*/  H_FREE_RESOURCE ; 
 scalar_t__ H_HARDWARE ; 
 scalar_t__ H_RESOURCE ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,...) ; 
 scalar_t__ ehca_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hcp_galpas_dtor (int /*<<< orphan*/ *) ; 

u64 hipz_h_destroy_qp(const struct ipz_adapter_handle adapter_handle,
		      struct ehca_qp *qp)
{
	u64 ret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	ret = hcp_galpas_dtor(&qp->galpas);
	if (ret) {
		ehca_gen_err("Could not destruct qp->galpas");
		return H_RESOURCE;
	}
	ret = ehca_plpar_hcall9(H_DISABLE_AND_GETC, outs,
				adapter_handle.handle,     /* r4 */
				/* function code */
				1,	                   /* r5 */
				qp->ipz_qp_handle.handle,  /* r6 */
				0, 0, 0, 0, 0, 0);
	if (ret == H_HARDWARE)
		ehca_gen_err("HCA not operational. ret=%lli", ret);

	ret = ehca_plpar_hcall_norets(H_FREE_RESOURCE,
				      adapter_handle.handle,     /* r4 */
				      qp->ipz_qp_handle.handle,  /* r5 */
				      0, 0, 0, 0, 0);

	if (ret == H_RESOURCE)
		ehca_gen_err("Resource still in use. ret=%lli", ret);

	return ret;
}