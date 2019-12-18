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
typedef  int u8 ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_STCFG2 ; 
 int /*<<< orphan*/  MEM_STTIME2 ; 
 int /*<<< orphan*/  PIO0 ; 
 int /*<<< orphan*/  PIO1 ; 
 int /*<<< orphan*/  PIO2 ; 
 int /*<<< orphan*/  PIO3 ; 
 int /*<<< orphan*/  PIO4 ; 
 int SBC_IDE_PIO0_TCSOE ; 
 int SBC_IDE_PIO0_TOECS ; 
 int SBC_IDE_PIO1_TCSOE ; 
 int SBC_IDE_PIO1_TOECS ; 
 int SBC_IDE_PIO2_TCSOE ; 
 int SBC_IDE_PIO2_TOECS ; 
 int SBC_IDE_PIO3_TCSOE ; 
 int SBC_IDE_PIO3_TOECS ; 
 int SBC_IDE_PIO4_TCSOE ; 
 int SBC_IDE_PIO4_TOECS ; 
 int SBC_IDE_TIMING (int /*<<< orphan*/ ) ; 
 int TCSOE_MASK ; 
 int TOECS_MASK ; 
 int TS_MASK ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1xxx_set_pio_mode(ide_drive_t *drive, const u8 pio)
{
	int mem_sttime = 0, mem_stcfg = au_readl(MEM_STCFG2);

	/* set pio mode! */
	switch(pio) {
	case 0:
		mem_sttime = SBC_IDE_TIMING(PIO0);

		/* set configuration for RCS2# */
		mem_stcfg |= TS_MASK;
		mem_stcfg &= ~TCSOE_MASK;
		mem_stcfg &= ~TOECS_MASK;
		mem_stcfg |= SBC_IDE_PIO0_TCSOE | SBC_IDE_PIO0_TOECS;
		break;

	case 1:
		mem_sttime = SBC_IDE_TIMING(PIO1);

		/* set configuration for RCS2# */
		mem_stcfg |= TS_MASK;
		mem_stcfg &= ~TCSOE_MASK;
		mem_stcfg &= ~TOECS_MASK;
		mem_stcfg |= SBC_IDE_PIO1_TCSOE | SBC_IDE_PIO1_TOECS;
		break;

	case 2:
		mem_sttime = SBC_IDE_TIMING(PIO2);

		/* set configuration for RCS2# */
		mem_stcfg &= ~TS_MASK;
		mem_stcfg &= ~TCSOE_MASK;
		mem_stcfg &= ~TOECS_MASK;
		mem_stcfg |= SBC_IDE_PIO2_TCSOE | SBC_IDE_PIO2_TOECS;
		break;

	case 3:
		mem_sttime = SBC_IDE_TIMING(PIO3);

		/* set configuration for RCS2# */
		mem_stcfg &= ~TS_MASK;
		mem_stcfg &= ~TCSOE_MASK;
		mem_stcfg &= ~TOECS_MASK;
		mem_stcfg |= SBC_IDE_PIO3_TCSOE | SBC_IDE_PIO3_TOECS;

		break;

	case 4:
		mem_sttime = SBC_IDE_TIMING(PIO4);

		/* set configuration for RCS2# */
		mem_stcfg &= ~TS_MASK;
		mem_stcfg &= ~TCSOE_MASK;
		mem_stcfg &= ~TOECS_MASK;
		mem_stcfg |= SBC_IDE_PIO4_TCSOE | SBC_IDE_PIO4_TOECS;
		break;
	}

	au_writel(mem_sttime,MEM_STTIME2);
	au_writel(mem_stcfg,MEM_STCFG2);
}