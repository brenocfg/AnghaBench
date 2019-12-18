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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct hipz_query_port {int dummy; } ;

/* Variables and functions */
 int EHCA_PAGESIZE ; 
 int H_PARAMETER ; 
 int /*<<< orphan*/  H_QUERY_PORT ; 
 int ehca_debug_level ; 
 int /*<<< orphan*/  ehca_dmp (struct hipz_query_port*,int,char*) ; 
 int /*<<< orphan*/  ehca_gen_err (char*) ; 
 int ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virt_to_abs (struct hipz_query_port*) ; 

u64 hipz_h_query_port(const struct ipz_adapter_handle adapter_handle,
		      const u8 port_id,
		      struct hipz_query_port *query_port_response_block)
{
	u64 ret;
	u64 r_cb = virt_to_abs(query_port_response_block);

	if (r_cb & (EHCA_PAGESIZE-1)) {
		ehca_gen_err("response block not page aligned");
		return H_PARAMETER;
	}

	ret = ehca_plpar_hcall_norets(H_QUERY_PORT,
				      adapter_handle.handle, /* r4 */
				      port_id,	             /* r5 */
				      r_cb,	             /* r6 */
				      0, 0, 0, 0);

	if (ehca_debug_level >= 2)
		ehca_dmp(query_port_response_block, 64, "response_block");

	return ret;
}