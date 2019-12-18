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
 int /*<<< orphan*/  ANTIC_CHACTL ; 
 int /*<<< orphan*/  ANTIC_CHBASE ; 
 int /*<<< orphan*/  ANTIC_DMACTL ; 
 int /*<<< orphan*/  ANTIC_HSCROL ; 
 int /*<<< orphan*/  ANTIC_NMIEN ; 
 int /*<<< orphan*/  ANTIC_NMIST ; 
 int /*<<< orphan*/  ANTIC_OFFSET_CHACTL ; 
 int /*<<< orphan*/  ANTIC_OFFSET_CHBASE ; 
 int /*<<< orphan*/  ANTIC_OFFSET_DMACTL ; 
 int /*<<< orphan*/  ANTIC_OFFSET_PMBASE ; 
 int /*<<< orphan*/  ANTIC_PMBASE ; 
 int /*<<< orphan*/  ANTIC_PutByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ANTIC_VSCROL ; 
 int /*<<< orphan*/  ANTIC_dlist ; 
 int /*<<< orphan*/  ANTIC_xpos ; 
 int /*<<< orphan*/  ANTIC_xpos_limit ; 
 int /*<<< orphan*/  ANTIC_ypos ; 
 int /*<<< orphan*/  IR ; 
 int /*<<< orphan*/  StateSav_ReadINT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StateSav_ReadUBYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StateSav_ReadUWORD (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  anticmode ; 
 int /*<<< orphan*/  dctr ; 
 int /*<<< orphan*/  lastline ; 
 int /*<<< orphan*/  need_dl ; 
 int /*<<< orphan*/  screenaddr ; 
 int /*<<< orphan*/  vscrol_off ; 

void ANTIC_StateRead(void)
{
	StateSav_ReadUBYTE(&ANTIC_DMACTL, 1);
	StateSav_ReadUBYTE(&ANTIC_CHACTL, 1);
	StateSav_ReadUBYTE(&ANTIC_HSCROL, 1);
	StateSav_ReadUBYTE(&ANTIC_VSCROL, 1);
	StateSav_ReadUBYTE(&ANTIC_PMBASE, 1);
	StateSav_ReadUBYTE(&ANTIC_CHBASE, 1);
	StateSav_ReadUBYTE(&ANTIC_NMIEN, 1);
	StateSav_ReadUBYTE(&ANTIC_NMIST, 1);
	StateSav_ReadUBYTE(&IR, 1);
	StateSav_ReadUBYTE(&anticmode, 1);
	StateSav_ReadUBYTE(&dctr, 1);
	StateSav_ReadUBYTE(&lastline, 1);
	StateSav_ReadUBYTE(&need_dl, 1);
	StateSav_ReadUBYTE(&vscrol_off, 1);

	StateSav_ReadUWORD(&ANTIC_dlist, 1);
	StateSav_ReadUWORD(&screenaddr, 1);

	StateSav_ReadINT(&ANTIC_xpos, 1);
	StateSav_ReadINT(&ANTIC_xpos_limit, 1);
	StateSav_ReadINT(&ANTIC_ypos, 1);

	ANTIC_PutByte(ANTIC_OFFSET_DMACTL, ANTIC_DMACTL);
	ANTIC_PutByte(ANTIC_OFFSET_CHACTL, ANTIC_CHACTL);
	ANTIC_PutByte(ANTIC_OFFSET_PMBASE, ANTIC_PMBASE);
	ANTIC_PutByte(ANTIC_OFFSET_CHBASE, ANTIC_CHBASE);
}