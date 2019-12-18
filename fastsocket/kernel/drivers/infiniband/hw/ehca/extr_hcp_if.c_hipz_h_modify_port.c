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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCA_BMASK_SET (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  H_MODIFY_PORT ; 
 int /*<<< orphan*/  H_MP_INIT_TYPE ; 
 int /*<<< orphan*/  H_MP_RESET_QKEY_CTR ; 
 int /*<<< orphan*/  H_MP_SHUTDOWN ; 
 int const IB_PORT_INIT_TYPE ; 
 int const IB_PORT_RESET_QKEY_CNTR ; 
 int const IB_PORT_SHUTDOWN ; 
 int /*<<< orphan*/  ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_modify_port(const struct ipz_adapter_handle adapter_handle,
		       const u8 port_id, const u32 port_cap,
		       const u8 init_type, const int modify_mask)
{
	u64 port_attributes = port_cap;

	if (modify_mask & IB_PORT_SHUTDOWN)
		port_attributes |= EHCA_BMASK_SET(H_MP_SHUTDOWN, 1);
	if (modify_mask & IB_PORT_INIT_TYPE)
		port_attributes |= EHCA_BMASK_SET(H_MP_INIT_TYPE, init_type);
	if (modify_mask & IB_PORT_RESET_QKEY_CNTR)
		port_attributes |= EHCA_BMASK_SET(H_MP_RESET_QKEY_CTR, 1);

	return ehca_plpar_hcall_norets(H_MODIFY_PORT,
				       adapter_handle.handle, /* r4 */
				       port_id,               /* r5 */
				       port_attributes,       /* r6 */
				       0, 0, 0, 0);
}