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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_prog_hw(uint8_t *hwreg,
	uint32_t *inptr, uint32_t regcnt)
{
	/* unsigned long flags; */
	uint32_t i;
	uint32_t *p;

	/* @todo This is causing issues, need further investigate */
	/* spin_lock_irqsave(&ctrl->io_lock, flags); */

	p = (uint32_t *)(hwreg);
	for (i = 0; i < (regcnt >> 2); i++)
		writel(*inptr++, p++);
		/* *p++ = *inptr++; */

	/* spin_unlock_irqrestore(&ctrl->io_lock, flags); */
}