#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct hipz_query_hca {int dummy; } ;

/* Variables and functions */
 int EHCA_PAGESIZE ; 
 int H_PARAMETER ; 
 int /*<<< orphan*/  H_QUERY_HCA ; 
 int /*<<< orphan*/  ehca_gen_err (char*,struct hipz_query_hca*) ; 
 int ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virt_to_abs (struct hipz_query_hca*) ; 

u64 hipz_h_query_hca(const struct ipz_adapter_handle adapter_handle,
		     struct hipz_query_hca *query_hca_rblock)
{
	u64 r_cb = virt_to_abs(query_hca_rblock);

	if (r_cb & (EHCA_PAGESIZE-1)) {
		ehca_gen_err("response_block=%p not page aligned",
			     query_hca_rblock);
		return H_PARAMETER;
	}

	return ehca_plpar_hcall_norets(H_QUERY_HCA,
				       adapter_handle.handle, /* r4 */
				       r_cb,                  /* r5 */
				       0, 0, 0, 0, 0);
}