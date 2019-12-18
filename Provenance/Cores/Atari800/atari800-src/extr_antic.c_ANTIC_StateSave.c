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
 int /*<<< orphan*/  ANTIC_PMBASE ; 
 int /*<<< orphan*/  ANTIC_VSCROL ; 
 int /*<<< orphan*/  ANTIC_dlist ; 
 int /*<<< orphan*/  ANTIC_xpos ; 
 int /*<<< orphan*/  ANTIC_xpos_limit ; 
 int /*<<< orphan*/  ANTIC_ypos ; 
 int /*<<< orphan*/  IR ; 
 int /*<<< orphan*/  StateSav_SaveINT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StateSav_SaveUBYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StateSav_SaveUWORD (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  anticmode ; 
 int /*<<< orphan*/  dctr ; 
 int /*<<< orphan*/  lastline ; 
 int /*<<< orphan*/  need_dl ; 
 int /*<<< orphan*/  screenaddr ; 
 int /*<<< orphan*/  vscrol_off ; 

void ANTIC_StateSave(void)
{
	StateSav_SaveUBYTE(&ANTIC_DMACTL, 1);
	StateSav_SaveUBYTE(&ANTIC_CHACTL, 1);
	StateSav_SaveUBYTE(&ANTIC_HSCROL, 1);
	StateSav_SaveUBYTE(&ANTIC_VSCROL, 1);
	StateSav_SaveUBYTE(&ANTIC_PMBASE, 1);
	StateSav_SaveUBYTE(&ANTIC_CHBASE, 1);
	StateSav_SaveUBYTE(&ANTIC_NMIEN, 1);
	StateSav_SaveUBYTE(&ANTIC_NMIST, 1);
	StateSav_SaveUBYTE(&IR, 1);
	StateSav_SaveUBYTE(&anticmode, 1);
	StateSav_SaveUBYTE(&dctr, 1);
	StateSav_SaveUBYTE(&lastline, 1);
	StateSav_SaveUBYTE(&need_dl, 1);
	StateSav_SaveUBYTE(&vscrol_off, 1);

	StateSav_SaveUWORD(&ANTIC_dlist, 1);
	StateSav_SaveUWORD(&screenaddr, 1);

	StateSav_SaveINT(&ANTIC_xpos, 1);
	StateSav_SaveINT(&ANTIC_xpos_limit, 1);
	StateSav_SaveINT(&ANTIC_ypos, 1);
}