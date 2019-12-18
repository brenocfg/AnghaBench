#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ model; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  DDB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSP_DATA_AVAIL ; 
 int /*<<< orphan*/  DSP_READ ; 
 int /*<<< orphan*/  DSP_RESET ; 
 scalar_t__ MDL_ESS ; 
 int ess_dsp_reset (TYPE_1__*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int sb_dsp_reset(sb_devc * devc)
{
	int loopc;

	DEB(printk("Entered sb_dsp_reset()\n"));

	if (devc->model == MDL_ESS) return ess_dsp_reset (devc);

	/* This is only for non-ESS chips */

	outb(1, DSP_RESET);

	udelay(10);
	outb(0, DSP_RESET);
	udelay(30);

	for (loopc = 0; loopc < 1000 && !(inb(DSP_DATA_AVAIL) & 0x80); loopc++);

	if (inb(DSP_READ) != 0xAA)
	{
		DDB(printk("sb: No response to RESET\n"));
		return 0;	/* Sorry */
	}

	DEB(printk("sb_dsp_reset() OK\n"));

	return 1;
}