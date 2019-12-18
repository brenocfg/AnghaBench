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
typedef  unsigned int u32 ;
struct mc13783 {int /*<<< orphan*/  spi_device; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MC13783_FRAME_MASK ; 
 int MC13783_MAX_REG_NUM ; 
 int MC13783_REG_NUM_SHIFT ; 
 int MC13783_WRITE_BIT_SHIFT ; 
 int spi_rw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mc13783_write(struct mc13783 *mc13783, int reg_num, u32 reg_val)
{
	unsigned int frame = 0;

	if (reg_num > MC13783_MAX_REG_NUM)
		return -EINVAL;

	frame |= (1 << MC13783_WRITE_BIT_SHIFT);
	frame |= reg_num << MC13783_REG_NUM_SHIFT;
	frame |= reg_val & MC13783_FRAME_MASK;

	return spi_rw(mc13783->spi_device, (u8 *)&frame, 4);
}