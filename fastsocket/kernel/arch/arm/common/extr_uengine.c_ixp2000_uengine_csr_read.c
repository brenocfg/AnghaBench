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

/* Variables and functions */
 int LOCAL_CSR_STATUS ; 
 int ixp2000_reg_read (int*) ; 
 void* ixp2000_uengine_csr_area (int) ; 

u32 ixp2000_uengine_csr_read(int uengine, int offset)
{
	void *uebase;
	u32 *local_csr_status;
	u32 *reg;
	u32 value;

	uebase = ixp2000_uengine_csr_area(uengine);

	local_csr_status = (u32 *)(uebase + LOCAL_CSR_STATUS);
	reg = (u32 *)(uebase + offset);
	do {
		value = ixp2000_reg_read(reg);
	} while (ixp2000_reg_read(local_csr_status) & 1);

	return value;
}