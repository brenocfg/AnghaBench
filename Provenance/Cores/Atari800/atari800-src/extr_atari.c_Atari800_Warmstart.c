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

/* Variables and functions */
 int ANTIC_NMIST ; 
 int /*<<< orphan*/  ANTIC_Reset () ; 
 scalar_t__ Atari800_MACHINE_800 ; 
 scalar_t__ Atari800_machine_type ; 
 int /*<<< orphan*/  CPU_NMI () ; 
 int /*<<< orphan*/  CPU_Reset () ; 
 int /*<<< orphan*/  HandleResetEvent () ; 
 int /*<<< orphan*/  MEMORY_PutByte (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MEMORY_axlon_num_banks ; 
 int /*<<< orphan*/  PBI_Reset () ; 
 int /*<<< orphan*/  PIA_Reset () ; 

void Atari800_Warmstart(void)
{
	if (Atari800_machine_type == Atari800_MACHINE_800) {
		/* A real Axlon homebanks on reset */
		/* XXX: what does Mosaic do? */
		if (MEMORY_axlon_num_banks > 0) MEMORY_PutByte(0xcfff, 0);
		/* RESET key in 400/800 does not reset chips,
		   but only generates RNMI interrupt */
		ANTIC_NMIST = 0x3f;
		CPU_NMI();
	}
	else {
		PBI_Reset();
		PIA_Reset();
		ANTIC_Reset();
		/* CPU_Reset() must be after PIA_Reset(),
		   because Reset routine vector must be read from OS ROM */
		CPU_Reset();
		/* note: POKEY and GTIA have no Reset pin */
	}
#ifdef __PLUS
	HandleResetEvent();
#endif
}