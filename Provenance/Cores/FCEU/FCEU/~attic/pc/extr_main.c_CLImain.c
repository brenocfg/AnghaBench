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
 int /*<<< orphan*/  CloseGame () ; 
 int /*<<< orphan*/  CreateDirs () ; 
 scalar_t__ CurGame ; 
 int /*<<< orphan*/  DoArgs (int,char**) ; 
 int /*<<< orphan*/  DoFun () ; 
 int /*<<< orphan*/  DrBaseDirectory ; 
 int /*<<< orphan*/  DriverKill () ; 
 int FCEUI_Initialize () ; 
 int /*<<< orphan*/  FCEUI_Kill () ; 
 int /*<<< orphan*/  FCEUI_SetBaseDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCEUI_SetNTSCTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetBaseDirectory () ; 
 int /*<<< orphan*/  LoadCPalette () ; 
 int /*<<< orphan*/  LoadConfig () ; 
 int /*<<< orphan*/  LoadGame (char*) ; 
 int /*<<< orphan*/  SaveConfig () ; 
 int /*<<< orphan*/  ShowUsage (char*) ; 
 scalar_t__ cpalette ; 
 int /*<<< orphan*/  ntsccol ; 
 int /*<<< orphan*/  ntschue ; 
 int /*<<< orphan*/  ntsctint ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int CLImain(int argc, char *argv[])
{
	int ret;

	if(!(ret=FCEUI_Initialize()))
         return(0);

        DrBaseDirectory=GetBaseDirectory();
	FCEUI_SetBaseDirectory(DrBaseDirectory);

	CreateDirs();

	#ifdef EXTGUI
	if(argc==2 && !strcmp(argv[1],"-help")) // I hope no one has a game named "-help" :b
	#else
        if(argc<=1) 
	#endif
        {
         ShowUsage(argv[0]);
         return(0);
        }

        LoadConfig();
        DoArgs(argc-2,&argv[1]);
	FCEUI_SetNTSCTH(ntsccol, ntsctint, ntschue);
	if(cpalette)
	 LoadCPalette();

	/* All the config files and arguments are parsed now. */
	#ifdef EXTGUI
        return(1);

	#else
        if(!LoadGame(argv[argc-1]))
        {
         DriverKill();
         return(0);
        }

	while(CurGame)
	 DoFun();

	#if(0)
	{
	 int x;
	 for(x=1;x<argc;x++) 
         { LoadGame(argv[x]); while(CurGame) DoFun(); }
	}
	#endif

        CloseGame();
        
	SaveConfig();

        FCEUI_Kill();

	#endif
        return(1);
}