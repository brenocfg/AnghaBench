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
struct ehca_eq {TYPE_1__ ipz_eq_handle; int /*<<< orphan*/  galpas; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_FREE_RESOURCE ; 
 scalar_t__ H_RESOURCE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,...) ; 
 scalar_t__ ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hcp_galpas_dtor (int /*<<< orphan*/ *) ; 

u64 hipz_h_destroy_eq(const struct ipz_adapter_handle adapter_handle,
		      struct ehca_eq *eq)
{
	u64 ret;

	ret = hcp_galpas_dtor(&eq->galpas);
	if (ret) {
		ehca_gen_err("Could not destruct eq->galpas");
		return H_RESOURCE;
	}

	ret = ehca_plpar_hcall_norets(H_FREE_RESOURCE,
				      adapter_handle.handle,     /* r4 */
				      eq->ipz_eq_handle.handle,  /* r5 */
				      0, 0, 0, 0, 0);

	if (ret == H_RESOURCE)
		ehca_gen_err("Resource in use. ret=%lli ", ret);

	return ret;
}