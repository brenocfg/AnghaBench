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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static void vfe_read_reg_values(uint8_t *hwreg,
	uint32_t *dest, uint32_t count)
{
	/* unsigned long flags; */
	uint32_t *temp;
	uint32_t i;

	/* @todo This is causing issues, need further investigate */
	/* spin_lock_irqsave(&ctrl->io_lock, flags); */

	temp = (uint32_t *)(hwreg);
	for (i = 0; i < count; i++)
		*dest++ = *temp++;

	/* spin_unlock_irqrestore(&ctrl->io_lock, flags); */
}