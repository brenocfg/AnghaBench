#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mobj_t ;
struct TYPE_11__ {int special; size_t* sidenum; } ;
typedef  TYPE_2__ line_t ;
typedef  int /*<<< orphan*/  button_t ;
struct TYPE_12__ {int basepic; int numpics; int speed; scalar_t__ istexture; } ;
typedef  TYPE_3__ anim_t ;
struct TYPE_14__ {int where; int /*<<< orphan*/  soundorg; int /*<<< orphan*/  btexture; TYPE_1__* line; scalar_t__ btimer; } ;
struct TYPE_13__ {int /*<<< orphan*/  bottomtexture; int /*<<< orphan*/  midtexture; int /*<<< orphan*/  toptexture; int /*<<< orphan*/  textureoffset; } ;
struct TYPE_10__ {size_t* sidenum; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRACUNIT ; 
 int /*<<< orphan*/  G_ExitLevel () ; 
 int MAXBUTTONS ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* anims ; 
#define  bottom 130 
 TYPE_5__* buttonlist ; 
 int* flattranslation ; 
 TYPE_3__* lastanim ; 
 int /*<<< orphan*/  levelTimeCount ; 
 int levelTimer ; 
 int leveltime ; 
 TYPE_2__** linespeciallist ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
#define  middle 129 
 int numlinespecials ; 
 int /*<<< orphan*/  sfx_swtchn ; 
 TYPE_4__* sides ; 
 int* texturetranslation ; 
#define  top 128 

void P_UpdateSpecials (void)
{
    anim_t*	anim;
    int		pic;
    int		i;
    line_t*	line;

    
    //	LEVEL TIMER
    if (levelTimer == true)
    {
	levelTimeCount--;
	if (!levelTimeCount)
	    G_ExitLevel();
    }
    
    //	ANIMATE FLATS AND TEXTURES GLOBALLY
    for (anim = anims ; anim < lastanim ; anim++)
    {
	for (i=anim->basepic ; i<anim->basepic+anim->numpics ; i++)
	{
	    pic = anim->basepic + ( (leveltime/anim->speed + i)%anim->numpics );
	    if (anim->istexture)
		texturetranslation[i] = pic;
	    else
		flattranslation[i] = pic;
	}
    }

    
    //	ANIMATE LINE SPECIALS
    for (i = 0; i < numlinespecials; i++)
    {
	line = linespeciallist[i];
	switch(line->special)
	{
	  case 48:
	    // EFFECT FIRSTCOL SCROLL +
	    sides[line->sidenum[0]].textureoffset += FRACUNIT;
	    break;
	}
    }

    
    //	DO BUTTONS
    for (i = 0; i < MAXBUTTONS; i++)
	if (buttonlist[i].btimer)
	{
	    buttonlist[i].btimer--;
	    if (!buttonlist[i].btimer)
	    {
		switch(buttonlist[i].where)
		{
		  case top:
		    sides[buttonlist[i].line->sidenum[0]].toptexture =
			buttonlist[i].btexture;
		    break;
		    
		  case middle:
		    sides[buttonlist[i].line->sidenum[0]].midtexture =
			buttonlist[i].btexture;
		    break;
		    
		  case bottom:
		    sides[buttonlist[i].line->sidenum[0]].bottomtexture =
			buttonlist[i].btexture;
		    break;
		}
		S_StartSound((mobj_t *)&buttonlist[i].soundorg,sfx_swtchn);
		memset(&buttonlist[i],0,sizeof(button_t));
	    }
	}
	
}