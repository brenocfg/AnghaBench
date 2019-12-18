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
struct hcp_modify_qp_control_block {int dummy; } ;
struct h_galpa {int dummy; } ;
struct ehca_pfqp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_QUERY_QP ; 
 int /*<<< orphan*/  ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_abs (struct hcp_modify_qp_control_block*) ; 

u64 hipz_h_query_qp(const struct ipz_adapter_handle adapter_handle,
		    const struct ipz_qp_handle qp_handle,
		    struct ehca_pfqp *pfqp,
		    struct hcp_modify_qp_control_block *qqpcb,
		    struct h_galpa gal)
{
	return ehca_plpar_hcall_norets(H_QUERY_QP,
				       adapter_handle.handle, /* r4 */
				       qp_handle.handle,      /* r5 */
				       virt_to_abs(qqpcb),    /* r6 */
				       0, 0, 0, 0);
}