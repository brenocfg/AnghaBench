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
struct azx {scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLBASE ; 
 int /*<<< orphan*/  DPUBASE ; 
 int /*<<< orphan*/  azx_free_cmd_io (struct azx*) ; 
 int /*<<< orphan*/  azx_int_clear (struct azx*) ; 
 int /*<<< orphan*/  azx_int_disable (struct azx*) ; 
 int /*<<< orphan*/  azx_writel (struct azx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void azx_stop_chip(struct azx *chip)
{
	if (!chip->initialized)
		return;

	/* disable interrupts */
	azx_int_disable(chip);
	azx_int_clear(chip);

	/* disable CORB/RIRB */
	azx_free_cmd_io(chip);

	/* disable position buffer */
	azx_writel(chip, DPLBASE, 0);
	azx_writel(chip, DPUBASE, 0);

	chip->initialized = 0;
}