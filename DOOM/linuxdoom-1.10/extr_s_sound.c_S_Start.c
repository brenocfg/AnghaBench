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
struct TYPE_2__ {scalar_t__ sfxinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ChangeMusic (int,int) ; 
 int /*<<< orphan*/  S_StopChannel (int) ; 
 TYPE_1__* channels ; 
 scalar_t__ commercial ; 
 int gameepisode ; 
 int gamemap ; 
 scalar_t__ gamemode ; 
 int mus_e1m1 ; 
 int mus_e1m5 ; 
 int mus_e1m9 ; 
 int mus_e2m4 ; 
 int mus_e2m5 ; 
 int mus_e2m6 ; 
 int mus_e2m7 ; 
 int mus_e3m2 ; 
 int mus_e3m3 ; 
 int mus_e3m4 ; 
 scalar_t__ mus_paused ; 
 int mus_runnin ; 
 int nextcleanup ; 
 int numChannels ; 

void S_Start(void)
{
  int cnum;
  int mnum;

  // kill all playing sounds at start of level
  //  (trust me - a good idea)
  for (cnum=0 ; cnum<numChannels ; cnum++)
    if (channels[cnum].sfxinfo)
      S_StopChannel(cnum);
  
  // start new music for the level
  mus_paused = 0;
  
  if (gamemode == commercial)
    mnum = mus_runnin + gamemap - 1;
  else
  {
    int spmus[]=
    {
      // Song - Who? - Where?
      
      mus_e3m4,	// American	e4m1
      mus_e3m2,	// Romero	e4m2
      mus_e3m3,	// Shawn	e4m3
      mus_e1m5,	// American	e4m4
      mus_e2m7,	// Tim 	e4m5
      mus_e2m4,	// Romero	e4m6
      mus_e2m6,	// J.Anderson	e4m7 CHIRON.WAD
      mus_e2m5,	// Shawn	e4m8
      mus_e1m9	// Tim		e4m9
    };
    
    if (gameepisode < 4)
      mnum = mus_e1m1 + (gameepisode-1)*9 + gamemap-1;
    else
      mnum = spmus[gamemap-1];
    }	
  
  // HACK FOR COMMERCIAL
  //  if (commercial && mnum > mus_e3m9)	
  //      mnum -= mus_e3m9;
  
  S_ChangeMusic(mnum, true);
  
  nextcleanup = 15;
}