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
typedef  int /*<<< orphan*/  u64 ;
struct ipz_qp_handle {int /*<<< orphan*/  handle; } ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct ehca_pfqp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_DISABLE_AND_GETC ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  ehca_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_disable_and_get_wqe(const struct ipz_adapter_handle adapter_handle,
			       const struct ipz_qp_handle qp_handle,
			       struct ehca_pfqp *pfqp,
			       void **log_addr_next_sq_wqe2processed,
			       void **log_addr_next_rq_wqe2processed,
			       int dis_and_get_function_code)
{
	u64 ret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	ret = ehca_plpar_hcall9(H_DISABLE_AND_GETC, outs,
				adapter_handle.handle,     /* r4 */
				dis_and_get_function_code, /* r5 */
				qp_handle.handle,	   /* r6 */
				0, 0, 0, 0, 0, 0);
	if (log_addr_next_sq_wqe2processed)
		*log_addr_next_sq_wqe2processed = (void *)outs[0];
	if (log_addr_next_rq_wqe2processed)
		*log_addr_next_rq_wqe2processed = (void *)outs[1];

	return ret;
}