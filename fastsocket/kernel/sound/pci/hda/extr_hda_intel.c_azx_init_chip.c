#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct azx {int initialized; TYPE_1__ posbuf; int /*<<< orphan*/  single_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLBASE ; 
 int /*<<< orphan*/  DPUBASE ; 
 int /*<<< orphan*/  azx_init_cmd_io (struct azx*) ; 
 int /*<<< orphan*/  azx_int_clear (struct azx*) ; 
 int /*<<< orphan*/  azx_int_enable (struct azx*) ; 
 int /*<<< orphan*/  azx_reset (struct azx*,int) ; 
 int /*<<< orphan*/  azx_writel (struct azx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void azx_init_chip(struct azx *chip, int full_reset)
{
	if (chip->initialized)
		return;

	/* reset controller */
	azx_reset(chip, full_reset);

	/* initialize interrupts */
	azx_int_clear(chip);
	azx_int_enable(chip);

	/* initialize the codec command I/O */
	if (!chip->single_cmd)
		azx_init_cmd_io(chip);

	/* program the position buffer */
	azx_writel(chip, DPLBASE, (u32)chip->posbuf.addr);
	azx_writel(chip, DPUBASE, upper_32_bits(chip->posbuf.addr));

	chip->initialized = 1;
}