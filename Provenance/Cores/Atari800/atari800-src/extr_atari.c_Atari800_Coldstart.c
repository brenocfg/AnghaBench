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
 int /*<<< orphan*/  AF80_InsertRightCartridge () ; 
 int /*<<< orphan*/  AF80_Reset () ; 
 scalar_t__ AF80_enabled ; 
 int /*<<< orphan*/  ANTIC_Reset () ; 
 int /*<<< orphan*/  CARTRIDGE_ColdStart () ; 
 int /*<<< orphan*/  CPU_Reset () ; 
 int GTIA_consol_override ; 
 int /*<<< orphan*/  HandleResetEvent () ; 
 int /*<<< orphan*/  MEMORY_dPutByte (int,int) ; 
 int /*<<< orphan*/  PBI_Reset () ; 
 int /*<<< orphan*/  PIA_Reset () ; 

void Atari800_Coldstart(void)
{
	PBI_Reset();
	PIA_Reset();
	ANTIC_Reset();
	/* CPU_Reset() must be after PIA_Reset(),
	   because Reset routine vector must be read from OS ROM */
	CPU_Reset();
	/* note: POKEY and GTIA have no Reset pin */
#ifdef __PLUS
	HandleResetEvent();
#endif
	/* reset cartridge to power-up state */
	CARTRIDGE_ColdStart();
	/* set Atari OS Coldstart flag */
	MEMORY_dPutByte(0x244, 1);
	/* handle Option key (disable BASIC in XL/XE)
	   and Start key (boot from cassette) */
	GTIA_consol_override = 2;
#ifdef AF80
	if (AF80_enabled) {
		AF80_Reset();
		AF80_InsertRightCartridge();
	}
#endif
}