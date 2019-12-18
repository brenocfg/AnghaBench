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
struct sep_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_SRAM_DATA_READY_REG_ADDR ; 
 int sep_read_reg (struct sep_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sep_wait_sram_write(struct sep_device *dev)
{
	u32 reg_val;
	do
		reg_val = sep_read_reg(dev, HW_SRAM_DATA_READY_REG_ADDR);
	while (!(reg_val & 1));
}