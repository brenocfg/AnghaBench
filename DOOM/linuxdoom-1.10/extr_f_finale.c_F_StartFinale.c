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
 int /*<<< orphan*/  GS_FINALE ; 
 int /*<<< orphan*/  S_ChangeMusic (int /*<<< orphan*/ ,int) ; 
 int automapactive ; 
 int /*<<< orphan*/  c1text ; 
 int /*<<< orphan*/  c2text ; 
 int /*<<< orphan*/  c3text ; 
 int /*<<< orphan*/  c4text ; 
 int /*<<< orphan*/  c5text ; 
 int /*<<< orphan*/  c6text ; 
#define  commercial 131 
 int /*<<< orphan*/  e1text ; 
 int /*<<< orphan*/  e2text ; 
 int /*<<< orphan*/  e3text ; 
 int /*<<< orphan*/  e4text ; 
 scalar_t__ finalecount ; 
 char* finaleflat ; 
 scalar_t__ finalestage ; 
 int /*<<< orphan*/  finaletext ; 
 int /*<<< orphan*/  ga_nothing ; 
 int /*<<< orphan*/  gameaction ; 
 int /*<<< orphan*/  gameepisode ; 
 int /*<<< orphan*/  gamemap ; 
 int gamemode ; 
 int /*<<< orphan*/  gamestate ; 
 int /*<<< orphan*/  mus_read_m ; 
 int /*<<< orphan*/  mus_victor ; 
#define  registered 130 
#define  retail 129 
#define  shareware 128 
 int viewactive ; 

void F_StartFinale (void)
{
    gameaction = ga_nothing;
    gamestate = GS_FINALE;
    viewactive = false;
    automapactive = false;

    // Okay - IWAD dependend stuff.
    // This has been changed severly, and
    //  some stuff might have changed in the process.
    switch ( gamemode )
    {

      // DOOM 1 - E1, E3 or E4, but each nine missions
      case shareware:
      case registered:
      case retail:
      {
	S_ChangeMusic(mus_victor, true);
	
	switch (gameepisode)
	{
	  case 1:
	    finaleflat = "FLOOR4_8";
	    finaletext = e1text;
	    break;
	  case 2:
	    finaleflat = "SFLR6_1";
	    finaletext = e2text;
	    break;
	  case 3:
	    finaleflat = "MFLR8_4";
	    finaletext = e3text;
	    break;
	  case 4:
	    finaleflat = "MFLR8_3";
	    finaletext = e4text;
	    break;
	  default:
	    // Ouch.
	    break;
	}
	break;
      }
      
      // DOOM II and missions packs with E1, M34
      case commercial:
      {
	  S_ChangeMusic(mus_read_m, true);

	  switch (gamemap)
	  {
	    case 6:
	      finaleflat = "SLIME16";
	      finaletext = c1text;
	      break;
	    case 11:
	      finaleflat = "RROCK14";
	      finaletext = c2text;
	      break;
	    case 20:
	      finaleflat = "RROCK07";
	      finaletext = c3text;
	      break;
	    case 30:
	      finaleflat = "RROCK17";
	      finaletext = c4text;
	      break;
	    case 15:
	      finaleflat = "RROCK13";
	      finaletext = c5text;
	      break;
	    case 31:
	      finaleflat = "RROCK19";
	      finaletext = c6text;
	      break;
	    default:
	      // Ouch.
	      break;
	  }
	  break;
      }	

   
      // Indeterminate.
      default:
	S_ChangeMusic(mus_read_m, true);
	finaleflat = "F_SKY1"; // Not used anywhere else.
	finaletext = c1text;  // FIXME - other text, music?
	break;
    }
    
    finalestage = 0;
    finalecount = 0;
	
}