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
struct twlreg_info {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_MODULE_PM_RECEIVER ; 
 int twl4030_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int
twl4030reg_write(struct twlreg_info *info, unsigned offset, u8 value)
{
	return twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER,
			value, info->base + offset);
}