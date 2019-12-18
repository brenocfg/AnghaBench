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
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {char* message; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*) ; 
 int /*<<< orphan*/  I_ReadScreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PU_CACHE ; 
 int /*<<< orphan*/  SCREENHEIGHT ; 
 int /*<<< orphan*/  SCREENWIDTH ; 
 int /*<<< orphan*/  W_CacheLumpName (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WritePCXfile (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 size_t consoleplayer ; 
 TYPE_1__* players ; 
 int /*<<< orphan*/ ** screens ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void M_ScreenShot (void)
{
    int		i;
    byte*	linear;
    char	lbmname[12];
    
    // munge planar buffer to linear
    linear = screens[2];
    I_ReadScreen (linear);
    
    // find a file name to save it to
    strcpy(lbmname,"DOOM00.pcx");
		
    for (i=0 ; i<=99 ; i++)
    {
	lbmname[4] = i/10 + '0';
	lbmname[5] = i%10 + '0';
	if (access(lbmname,0) == -1)
	    break;	// file doesn't exist
    }
    if (i==100)
	I_Error ("M_ScreenShot: Couldn't create a PCX");
    
    // save the pcx file
    WritePCXfile (lbmname, linear,
		  SCREENWIDTH, SCREENHEIGHT,
		  W_CacheLumpName ("PLAYPAL",PU_CACHE));
	
    players[consoleplayer].message = "screen shot";
}