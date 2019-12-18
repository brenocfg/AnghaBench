#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int special; } ;
typedef  TYPE_1__ sector_t ;
typedef  int /*<<< orphan*/  button_t ;
struct TYPE_12__ {int special; } ;

/* Variables and functions */
 int /*<<< orphan*/  FASTDARK ; 
 int MAXBUTTONS ; 
 int MAXCEILINGS ; 
 int MAXPLATS ; 
 int M_CheckParm (char*) ; 
 int /*<<< orphan*/  P_SpawnDoorCloseIn30 (TYPE_1__*) ; 
 int /*<<< orphan*/  P_SpawnDoorRaiseIn5Mins (TYPE_1__*,int) ; 
 int /*<<< orphan*/  P_SpawnFireFlicker (TYPE_1__*) ; 
 int /*<<< orphan*/  P_SpawnGlowingLight (TYPE_1__*) ; 
 int /*<<< orphan*/  P_SpawnLightFlash (TYPE_1__*) ; 
 int /*<<< orphan*/  P_SpawnStrobeFlash (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SLOWDARK ; 
 scalar_t__ W_CheckNumForName (char*) ; 
 int /*<<< orphan*/ ** activeceilings ; 
 int /*<<< orphan*/ ** activeplats ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * buttonlist ; 
 scalar_t__ deathmatch ; 
 int levelTimeCount ; 
 int levelTimer ; 
 TYPE_3__* lines ; 
 TYPE_3__** linespeciallist ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * myargv ; 
 int numlines ; 
 size_t numlinespecials ; 
 int numsectors ; 
 TYPE_1__* sectors ; 
 int /*<<< orphan*/  totalsecret ; 

void P_SpawnSpecials (void)
{
    sector_t*	sector;
    int		i;
    int		episode;

    episode = 1;
    if (W_CheckNumForName("texture2") >= 0)
	episode = 2;

    
    // See if -TIMER needs to be used.
    levelTimer = false;
	
    i = M_CheckParm("-avg");
    if (i && deathmatch)
    {
	levelTimer = true;
	levelTimeCount = 20 * 60 * 35;
    }
	
    i = M_CheckParm("-timer");
    if (i && deathmatch)
    {
	int	time;
	time = atoi(myargv[i+1]) * 60 * 35;
	levelTimer = true;
	levelTimeCount = time;
    }
    
    //	Init special SECTORs.
    sector = sectors;
    for (i=0 ; i<numsectors ; i++, sector++)
    {
	if (!sector->special)
	    continue;
	
	switch (sector->special)
	{
	  case 1:
	    // FLICKERING LIGHTS
	    P_SpawnLightFlash (sector);
	    break;

	  case 2:
	    // STROBE FAST
	    P_SpawnStrobeFlash(sector,FASTDARK,0);
	    break;
	    
	  case 3:
	    // STROBE SLOW
	    P_SpawnStrobeFlash(sector,SLOWDARK,0);
	    break;
	    
	  case 4:
	    // STROBE FAST/DEATH SLIME
	    P_SpawnStrobeFlash(sector,FASTDARK,0);
	    sector->special = 4;
	    break;
	    
	  case 8:
	    // GLOWING LIGHT
	    P_SpawnGlowingLight(sector);
	    break;
	  case 9:
	    // SECRET SECTOR
	    totalsecret++;
	    break;
	    
	  case 10:
	    // DOOR CLOSE IN 30 SECONDS
	    P_SpawnDoorCloseIn30 (sector);
	    break;
	    
	  case 12:
	    // SYNC STROBE SLOW
	    P_SpawnStrobeFlash (sector, SLOWDARK, 1);
	    break;

	  case 13:
	    // SYNC STROBE FAST
	    P_SpawnStrobeFlash (sector, FASTDARK, 1);
	    break;

	  case 14:
	    // DOOR RAISE IN 5 MINUTES
	    P_SpawnDoorRaiseIn5Mins (sector, i);
	    break;
	    
	  case 17:
	    P_SpawnFireFlicker(sector);
	    break;
	}
    }

    
    //	Init line EFFECTs
    numlinespecials = 0;
    for (i = 0;i < numlines; i++)
    {
	switch(lines[i].special)
	{
	  case 48:
	    // EFFECT FIRSTCOL SCROLL+
	    linespeciallist[numlinespecials] = &lines[i];
	    numlinespecials++;
	    break;
	}
    }

    
    //	Init other misc stuff
    for (i = 0;i < MAXCEILINGS;i++)
	activeceilings[i] = NULL;

    for (i = 0;i < MAXPLATS;i++)
	activeplats[i] = NULL;
    
    for (i = 0;i < MAXBUTTONS;i++)
	memset(&buttonlist[i],0,sizeof(button_t));

    // UNUSED: no horizonal sliders.
    //	P_InitSlidingDoorFrames();
}