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
typedef  scalar_t__ u32 ;
struct ipz_qp_handle {int /*<<< orphan*/  handle; } ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct h_galpa {int dummy; } ;

/* Variables and functions */
 scalar_t__ H_ALIAS_EXIST ; 
 int /*<<< orphan*/  H_DEFINE_AQP1 ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,scalar_t__) ; 
 scalar_t__ ehca_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_define_aqp1(const struct ipz_adapter_handle adapter_handle,
		       const struct ipz_qp_handle qp_handle,
		       struct h_galpa gal,
		       u32 port, u32 * pma_qp_nr,
		       u32 * bma_qp_nr)
{
	u64 ret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	ret = ehca_plpar_hcall9(H_DEFINE_AQP1, outs,
				adapter_handle.handle, /* r4 */
				qp_handle.handle,      /* r5 */
				port,	               /* r6 */
				0, 0, 0, 0, 0, 0);
	*pma_qp_nr = (u32)outs[0];
	*bma_qp_nr = (u32)outs[1];

	if (ret == H_ALIAS_EXIST)
		ehca_gen_err("AQP1 already exists. ret=%lli", ret);

	return ret;
}