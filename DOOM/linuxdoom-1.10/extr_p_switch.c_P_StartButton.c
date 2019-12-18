#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mobj_t ;
struct TYPE_6__ {TYPE_1__* frontsector; } ;
typedef  TYPE_2__ line_t ;
typedef  int /*<<< orphan*/  bwhere_e ;
struct TYPE_7__ {int btimer; int btexture; int /*<<< orphan*/ * soundorg; int /*<<< orphan*/  where; TYPE_2__* line; } ;
struct TYPE_5__ {int /*<<< orphan*/  soundorg; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*) ; 
 int MAXBUTTONS ; 
 TYPE_3__* buttonlist ; 

void
P_StartButton
( line_t*	line,
  bwhere_e	w,
  int		texture,
  int		time )
{
    int		i;
    
    // See if button is already pressed
    for (i = 0;i < MAXBUTTONS;i++)
    {
	if (buttonlist[i].btimer
	    && buttonlist[i].line == line)
	{
	    
	    return;
	}
    }
    

    
    for (i = 0;i < MAXBUTTONS;i++)
    {
	if (!buttonlist[i].btimer)
	{
	    buttonlist[i].line = line;
	    buttonlist[i].where = w;
	    buttonlist[i].btexture = texture;
	    buttonlist[i].btimer = time;
	    buttonlist[i].soundorg = (mobj_t *)&line->frontsector->soundorg;
	    return;
	}
    }
    
    I_Error("P_StartButton: no button slots left!");
}