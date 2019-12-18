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
typedef  int u32 ;
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 unsigned int ql_read_other_func_serdes_reg (struct ql_adapter*,int,int*) ; 
 unsigned int ql_read_serdes_reg (struct ql_adapter*,int,int*) ; 

__attribute__((used)) static void ql_get_both_serdes(struct ql_adapter *qdev, u32 addr,
			u32 *direct_ptr, u32 *indirect_ptr,
			unsigned int direct_valid, unsigned int indirect_valid)
{
	unsigned int status;

	status = 1;
	if (direct_valid)
		status = ql_read_serdes_reg(qdev, addr, direct_ptr);
	/* Dead fill any failures or invalids. */
	if (status)
		*direct_ptr = 0xDEADBEEF;

	status = 1;
	if (indirect_valid)
		status = ql_read_other_func_serdes_reg(
						qdev, addr, indirect_ptr);
	/* Dead fill any failures or invalids. */
	if (status)
		*indirect_ptr = 0xDEADBEEF;
}