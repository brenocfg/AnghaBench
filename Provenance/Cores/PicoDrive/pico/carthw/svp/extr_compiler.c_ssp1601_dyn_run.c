#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int emu_status; } ;

/* Variables and functions */
 int DUMP_BLOCK ; 
 int SSP_WAIT_MASK ; 
 TYPE_1__* ssp ; 
 int /*<<< orphan*/  ssp_drc_entry (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ssp_translate_block (int) ; 

void ssp1601_dyn_run(int cycles)
{
	if (ssp->emu_status & SSP_WAIT_MASK) return;

#ifdef DUMP_BLOCK
	ssp_translate_block(DUMP_BLOCK >> 1);
#endif
#ifdef __arm__
	ssp_drc_entry(ssp, cycles);
#endif
}