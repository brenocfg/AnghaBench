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

/* Variables and functions */
 int EHEA_BMASK_SET (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  H_REGISTER_HEA_RPAGES ; 
 int /*<<< orphan*/  H_REG_RPAGE_PAGE_SIZE ; 
 int /*<<< orphan*/  H_REG_RPAGE_QT ; 
 int ehea_plpar_hcall_norets (int /*<<< orphan*/ ,int const,int,int const,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_register_rpage(const u64 adapter_handle, const u8 pagesize,
			  const u8 queue_type, const u64 resource_handle,
			  const u64 log_pageaddr, u64 count)
{
	u64  reg_control;

	reg_control = EHEA_BMASK_SET(H_REG_RPAGE_PAGE_SIZE, pagesize)
		    | EHEA_BMASK_SET(H_REG_RPAGE_QT, queue_type);

	return ehea_plpar_hcall_norets(H_REGISTER_HEA_RPAGES,
				       adapter_handle,		/* R4 */
				       reg_control,		/* R5 */
				       resource_handle,		/* R6 */
				       log_pageaddr,		/* R7 */
				       count,			/* R8 */
				       0, 0);			/* R9-R10 */
}