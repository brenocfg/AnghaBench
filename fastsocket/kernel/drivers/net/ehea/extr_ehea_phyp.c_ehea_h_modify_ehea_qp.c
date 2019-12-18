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
typedef  scalar_t__ u8 ;
typedef  unsigned long u64 ;
typedef  unsigned long u16 ;

/* Variables and functions */
 int /*<<< orphan*/  H_MODIFY_HEA_QP ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 unsigned long ehea_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,unsigned long const,unsigned long,unsigned long const,unsigned long const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_abs (void*) ; 

u64 ehea_h_modify_ehea_qp(const u64 adapter_handle, const u8 cat,
			  const u64 qp_handle, const u64 sel_mask,
			  void *cb_addr, u64 *inv_attr_id, u64 *proc_mask,
			  u16 *out_swr, u16 *out_rwr)
{
	u64 hret;
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	hret = ehea_plpar_hcall9(H_MODIFY_HEA_QP,
				 outs,
				 adapter_handle,		/* R4 */
				 (u64) cat,			/* R5 */
				 qp_handle,			/* R6 */
				 sel_mask,			/* R7 */
				 virt_to_abs(cb_addr),		/* R8 */
				 0, 0, 0, 0);			/* R9-R12 */

	*inv_attr_id = outs[0];
	*out_swr = outs[3];
	*out_rwr = outs[4];
	*proc_mask = outs[5];

	return hret;
}