#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int special; size_t* sidenum; } ;
typedef  TYPE_1__ line_t ;
struct TYPE_8__ {int /*<<< orphan*/  soundorg; } ;
struct TYPE_7__ {int toptexture; int midtexture; int bottomtexture; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTONTIME ; 
 int /*<<< orphan*/  P_StartButton (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bottom ; 
 TYPE_3__* buttonlist ; 
 int /*<<< orphan*/  middle ; 
 int numswitches ; 
 int sfx_swtchn ; 
 int sfx_swtchx ; 
 TYPE_2__* sides ; 
 int* switchlist ; 
 int /*<<< orphan*/  top ; 

void
P_ChangeSwitchTexture
( line_t*	line,
  int 		useAgain )
{
    int     texTop;
    int     texMid;
    int     texBot;
    int     i;
    int     sound;
	
    if (!useAgain)
	line->special = 0;

    texTop = sides[line->sidenum[0]].toptexture;
    texMid = sides[line->sidenum[0]].midtexture;
    texBot = sides[line->sidenum[0]].bottomtexture;
	
    sound = sfx_swtchn;

    // EXIT SWITCH?
    if (line->special == 11)                
	sound = sfx_swtchx;
	
    for (i = 0;i < numswitches*2;i++)
    {
	if (switchlist[i] == texTop)
	{
	    S_StartSound(buttonlist->soundorg,sound);
	    sides[line->sidenum[0]].toptexture = switchlist[i^1];

	    if (useAgain)
		P_StartButton(line,top,switchlist[i],BUTTONTIME);

	    return;
	}
	else
	{
	    if (switchlist[i] == texMid)
	    {
		S_StartSound(buttonlist->soundorg,sound);
		sides[line->sidenum[0]].midtexture = switchlist[i^1];

		if (useAgain)
		    P_StartButton(line, middle,switchlist[i],BUTTONTIME);

		return;
	    }
	    else
	    {
		if (switchlist[i] == texBot)
		{
		    S_StartSound(buttonlist->soundorg,sound);
		    sides[line->sidenum[0]].bottomtexture = switchlist[i^1];

		    if (useAgain)
			P_StartButton(line, bottom,switchlist[i],BUTTONTIME);

		    return;
		}
	    }
	}
    }
}