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
 scalar_t__ CurGame ; 
 int /*<<< orphan*/  DriverKill () ; 
 int /*<<< orphan*/  FCEUI_CloseGame () ; 
 int /*<<< orphan*/  FCEUI_EndWaveRecord () ; 
 int /*<<< orphan*/  GUI_Hide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InputUserActiveFix () ; 
 scalar_t__ isloaded ; 
 scalar_t__ soundrecfn ; 

int CloseGame(void)
{
	if(!isloaded) return(0);
	FCEUI_CloseGame();
	DriverKill();
	isloaded=0;
	CurGame=0;

	if(soundrecfn)
         FCEUI_EndWaveRecord();

	#ifdef EXTGUI
	GUI_Hide(0);
	#endif
	InputUserActiveFix();
	return(1);
}