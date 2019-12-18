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
typedef  int /*<<< orphan*/  FCEUGI ;

/* Variables and functions */
 int /*<<< orphan*/  CloseGame () ; 
 int /*<<< orphan*/ * CurGame ; 
 int /*<<< orphan*/  DriverInitialize (int /*<<< orphan*/ *) ; 
 int EO_AUTOHIDE ; 
 int /*<<< orphan*/  FCEUD_NetworkConnect () ; 
 int /*<<< orphan*/  FCEUI_BeginWaveRecord (scalar_t__) ; 
 int /*<<< orphan*/ * FCEUI_LoadGame (char const*,int) ; 
 int /*<<< orphan*/  GUI_Hide (int) ; 
 int /*<<< orphan*/  ParseGI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RefreshThrottleFPS () ; 
 int eoptions ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int isloaded ; 
 scalar_t__ soundrecfn ; 

int LoadGame(const char *path)
{
	FCEUGI *tmp;

	CloseGame();
        if(!(tmp=FCEUI_LoadGame(path,1)))
	 return 0;
	CurGame=tmp;
        ParseGI(tmp);
        RefreshThrottleFPS();

        if(!DriverInitialize(tmp))
         return(0);  
	if(soundrecfn)
	{
	 if(!FCEUI_BeginWaveRecord(soundrecfn))
	 {
 	  free(soundrecfn);
	  soundrecfn=0;
	 }
	}
	isloaded=1;
	#ifdef EXTGUI
	if(eoptions&EO_AUTOHIDE) GUI_Hide(1);
	#endif

	FCEUD_NetworkConnect();
	return 1;
}