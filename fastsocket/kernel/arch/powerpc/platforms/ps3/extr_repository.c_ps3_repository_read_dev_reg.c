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
typedef  enum ps3_reg_type { ____Placeholder_ps3_reg_type } ps3_reg_type ;

/* Variables and functions */
 int ps3_repository_read_dev_reg_addr (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ps3_repository_read_dev_reg_type (unsigned int,unsigned int,unsigned int,int*) ; 

int ps3_repository_read_dev_reg(unsigned int bus_index,
	unsigned int dev_index, unsigned int reg_index,
	enum ps3_reg_type *reg_type, u64 *bus_addr, u64 *len)
{
	int result = ps3_repository_read_dev_reg_type(bus_index, dev_index,
		reg_index, reg_type);
	return result ? result
		: ps3_repository_read_dev_reg_addr(bus_index, dev_index,
		reg_index, bus_addr, len);
}