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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ H_BUSY ; 
 int /*<<< orphan*/  H_QUERY_INT_STATE ; 
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  ehca_gen_err (char*) ; 
 scalar_t__ ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_query_int_state(const struct ipz_adapter_handle adapter_handle,
			   u32 ist)
{
	u64 ret;
	ret = ehca_plpar_hcall_norets(H_QUERY_INT_STATE,
				      adapter_handle.handle, /* r4 */
				      ist,                   /* r5 */
				      0, 0, 0, 0, 0);

	if (ret != H_SUCCESS && ret != H_BUSY)
		ehca_gen_err("Could not query interrupt state.");

	return ret;
}