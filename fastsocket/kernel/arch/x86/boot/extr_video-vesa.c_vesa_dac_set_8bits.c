#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct biosregs {int ax; int bh; } ;
struct TYPE_4__ {scalar_t__ rsvd_pos; scalar_t__ blue_pos; scalar_t__ green_pos; scalar_t__ red_pos; void* rsvd_size; void* blue_size; void* green_size; void* red_size; } ;
struct TYPE_6__ {TYPE_1__ screen_info; } ;
struct TYPE_5__ {int capabilities; } ;

/* Variables and functions */
 TYPE_3__ boot_params ; 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 
 TYPE_2__ vginfo ; 

__attribute__((used)) static void vesa_dac_set_8bits(void)
{
	struct biosregs ireg, oreg;
	u8 dac_size = 6;

	/* If possible, switch the DAC to 8-bit mode */
	if (vginfo.capabilities & 1) {
		initregs(&ireg);
		ireg.ax = 0x4f08;
		ireg.bh = 0x08;
		intcall(0x10, &ireg, &oreg);
		if (oreg.ax == 0x004f)
			dac_size = oreg.bh;
	}

	/* Set the color sizes to the DAC size, and offsets to 0 */
	boot_params.screen_info.red_size   = dac_size;
	boot_params.screen_info.green_size = dac_size;
	boot_params.screen_info.blue_size  = dac_size;
	boot_params.screen_info.rsvd_size  = dac_size;

	boot_params.screen_info.red_pos    = 0;
	boot_params.screen_info.green_pos  = 0;
	boot_params.screen_info.blue_pos   = 0;
	boot_params.screen_info.rsvd_pos   = 0;
}