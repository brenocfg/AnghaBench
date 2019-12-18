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

/* Variables and functions */
 int EHCA_PAGESIZE ; 
 int /*<<< orphan*/  H_ERROR_DATA ; 
 int H_PARAMETER ; 
 int /*<<< orphan*/  ehca_gen_err (char*) ; 
 int ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virt_to_abs (void*) ; 

u64 hipz_h_error_data(const struct ipz_adapter_handle adapter_handle,
		      const u64 ressource_handle,
		      void *rblock,
		      unsigned long *byte_count)
{
	u64 r_cb = virt_to_abs(rblock);

	if (r_cb & (EHCA_PAGESIZE-1)) {
		ehca_gen_err("rblock not page aligned.");
		return H_PARAMETER;
	}

	return ehca_plpar_hcall_norets(H_ERROR_DATA,
				       adapter_handle.handle,
				       ressource_handle,
				       r_cb,
				       0, 0, 0, 0);
}