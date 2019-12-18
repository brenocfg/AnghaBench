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
struct ipz_qp_handle {int /*<<< orphan*/  handle; } ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct hcp_modify_qp_control_block {int dummy; } ;
struct h_galpa {int dummy; } ;
struct ehca_pfqp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_MODIFY_QP ; 
 scalar_t__ H_NOT_ENOUGH_RESOURCES ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,scalar_t__) ; 
 scalar_t__ ehca_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_abs (struct hcp_modify_qp_control_block*) ; 

u64 hipz_h_modify_qp(const struct ipz_adapter_handle adapter_handle,
		     const struct ipz_qp_handle qp_handle,
		     struct ehca_pfqp *pfqp,
		     const u64 update_mask,
		     struct hcp_modify_qp_control_block *mqpcb,
		     struct h_galpa gal)
{
	u64 ret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];
	ret = ehca_plpar_hcall9(H_MODIFY_QP, outs,
				adapter_handle.handle, /* r4 */
				qp_handle.handle,      /* r5 */
				update_mask,	       /* r6 */
				virt_to_abs(mqpcb),    /* r7 */
				0, 0, 0, 0, 0);

	if (ret == H_NOT_ENOUGH_RESOURCES)
		ehca_gen_err("Insufficient resources ret=%lli", ret);

	return ret;
}