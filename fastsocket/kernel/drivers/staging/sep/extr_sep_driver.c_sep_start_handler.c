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
struct sep_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_HOST_SEP_HOST_GPR0_REG_ADDR ; 
 int /*<<< orphan*/  HW_HOST_SEP_HOST_GPR3_REG_ADDR ; 
 int /*<<< orphan*/  dbg (char*) ; 
 unsigned long sep_read_reg (struct sep_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sep_start_handler(struct sep_device *sep)
{
	unsigned long reg_val;
	unsigned long error = 0;

	dbg("SEP Driver:--------> sep_start_handler start\n");

	/* wait in polling for message from SEP */
	do
		reg_val = sep_read_reg(sep, HW_HOST_SEP_HOST_GPR3_REG_ADDR);
	while (!reg_val);

	/* check the value */
	if (reg_val == 0x1)
		/* fatal error - read error status from GPRO */
		error = sep_read_reg(sep, HW_HOST_SEP_HOST_GPR0_REG_ADDR);
	dbg("SEP Driver:<-------- sep_start_handler end\n");
	return error;
}