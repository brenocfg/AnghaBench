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
struct TYPE_2__ {int /*<<< orphan*/  var; } ;
struct sa1100fb_info {int* palette_cpu; int reg_lccr3; int reg_lccr2; int reg_lccr1; int reg_lccr0; int dbar1; int dbar2; TYPE_1__ fb; } ;

/* Variables and functions */
 int DBAR1 ; 
 int DBAR2 ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int /*<<< orphan*/  GPDR ; 
 int /*<<< orphan*/  GPSR ; 
 int LCCR0 ; 
 int LCCR0_LEN ; 
 int LCCR1 ; 
 int LCCR2 ; 
 int LCCR3 ; 
 int /*<<< orphan*/  SHANNON_GPIO_DISP_EN ; 
 scalar_t__ machine_is_shannon () ; 
 int palette_pbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sa1100fb_enable_controller(struct sa1100fb_info *fbi)
{
	DPRINTK("Enabling LCD controller\n");

	/*
	 * Make sure the mode bits are present in the first palette entry
	 */
	fbi->palette_cpu[0] &= 0xcfff;
	fbi->palette_cpu[0] |= palette_pbs(&fbi->fb.var);

	/* Sequence from 11.7.10 */
	LCCR3 = fbi->reg_lccr3;
	LCCR2 = fbi->reg_lccr2;
	LCCR1 = fbi->reg_lccr1;
	LCCR0 = fbi->reg_lccr0 & ~LCCR0_LEN;
	DBAR1 = fbi->dbar1;
	DBAR2 = fbi->dbar2;
	LCCR0 |= LCCR0_LEN;

	if (machine_is_shannon()) {
		GPDR |= SHANNON_GPIO_DISP_EN;
		GPSR |= SHANNON_GPIO_DISP_EN;
	}

	DPRINTK("DBAR1 = 0x%08x\n", DBAR1);
	DPRINTK("DBAR2 = 0x%08x\n", DBAR2);
	DPRINTK("LCCR0 = 0x%08x\n", LCCR0);
	DPRINTK("LCCR1 = 0x%08x\n", LCCR1);
	DPRINTK("LCCR2 = 0x%08x\n", LCCR2);
	DPRINTK("LCCR3 = 0x%08x\n", LCCR3);
}