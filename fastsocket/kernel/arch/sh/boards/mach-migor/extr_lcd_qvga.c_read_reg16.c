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
struct sh_mobile_lcdc_sys_bus_ops {unsigned long (* read_data ) (void*) ;int /*<<< orphan*/  (* write_index ) (void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_reg18 (unsigned short) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 
 unsigned long stub2 (void*) ; 

__attribute__((used)) static unsigned long read_reg16(void *sys_ops_handle,
				struct sh_mobile_lcdc_sys_bus_ops *sys_ops,
				unsigned short reg)
{
	unsigned long data;

	sys_ops->write_index(sys_ops_handle, adjust_reg18(reg));
	data = sys_ops->read_data(sys_ops_handle);
	return ((data >> 1) & 0xff) | ((data >> 2) & 0xff00);
}