#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mo; } ;

/* Variables and functions */
 size_t BACKUPTICS ; 
 int /*<<< orphan*/  D_Display () ; 
 int /*<<< orphan*/  D_DoAdvanceDemo () ; 
 int /*<<< orphan*/  D_ProcessEvents () ; 
 int /*<<< orphan*/  G_BeginRecording () ; 
 int /*<<< orphan*/  G_BuildTiccmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_Ticker () ; 
 int /*<<< orphan*/  I_InitGraphics () ; 
 int /*<<< orphan*/  I_StartFrame () ; 
 int /*<<< orphan*/  I_StartTic () ; 
 int /*<<< orphan*/  I_SubmitSound () ; 
 int /*<<< orphan*/  I_UpdateSound () ; 
 scalar_t__ M_CheckParm (char*) ; 
 int /*<<< orphan*/  M_Ticker () ; 
 int /*<<< orphan*/  S_UpdateSounds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TryRunTics () ; 
 scalar_t__ advancedemo ; 
 int consoleplayer ; 
 int /*<<< orphan*/  debugfile ; 
 scalar_t__ demorecording ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  gametic ; 
 size_t maketic ; 
 int /*<<< orphan*/ ** netcmds ; 
 TYPE_1__* players ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ singletics ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void D_DoomLoop (void)
{
    if (demorecording)
	G_BeginRecording ();
		
    if (M_CheckParm ("-debugfile"))
    {
	char    filename[20];
	sprintf (filename,"debug%i.txt",consoleplayer);
	printf ("debug output to: %s\n",filename);
	debugfile = fopen (filename,"w");
    }
	
    I_InitGraphics ();

    while (1)
    {
	// frame syncronous IO operations
	I_StartFrame ();                
	
	// process one or more tics
	if (singletics)
	{
	    I_StartTic ();
	    D_ProcessEvents ();
	    G_BuildTiccmd (&netcmds[consoleplayer][maketic%BACKUPTICS]);
	    if (advancedemo)
		D_DoAdvanceDemo ();
	    M_Ticker ();
	    G_Ticker ();
	    gametic++;
	    maketic++;
	}
	else
	{
	    TryRunTics (); // will run at least one tic
	}
		
	S_UpdateSounds (players[consoleplayer].mo);// move positional sounds

	// Update display, next frame, with current state.
	D_Display ();

#ifndef SNDSERV
	// Sound mixing for the buffer is snychronous.
	I_UpdateSound();
#endif	
	// Synchronous sound output is explicitly called.
#ifndef SNDINTR
	// Update sound output.
	I_SubmitSound();
#endif
    }
}