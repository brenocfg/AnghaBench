#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fixedcolormap; int /*<<< orphan*/  viewz; int /*<<< orphan*/  extralight; TYPE_1__* mo; } ;
typedef  TYPE_2__ player_t ;
typedef  int /*<<< orphan*/  lighttable_t ;
struct TYPE_5__ {size_t angle; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 size_t ANGLETOFINESHIFT ; 
 int MAXLIGHTSCALE ; 
 scalar_t__ colormaps ; 
 int /*<<< orphan*/  extralight ; 
 int /*<<< orphan*/ * finecosine ; 
 int /*<<< orphan*/ * finesine ; 
 scalar_t__ fixedcolormap ; 
 int /*<<< orphan*/  framecount ; 
 scalar_t__* scalelightfixed ; 
 scalar_t__ sscount ; 
 int /*<<< orphan*/  validcount ; 
 size_t viewangle ; 
 size_t viewangleoffset ; 
 int /*<<< orphan*/  viewcos ; 
 TYPE_2__* viewplayer ; 
 int /*<<< orphan*/  viewsin ; 
 int /*<<< orphan*/  viewx ; 
 int /*<<< orphan*/  viewy ; 
 int /*<<< orphan*/  viewz ; 
 scalar_t__* walllights ; 

void R_SetupFrame (player_t* player)
{		
    int		i;
    
    viewplayer = player;
    viewx = player->mo->x;
    viewy = player->mo->y;
    viewangle = player->mo->angle + viewangleoffset;
    extralight = player->extralight;

    viewz = player->viewz;
    
    viewsin = finesine[viewangle>>ANGLETOFINESHIFT];
    viewcos = finecosine[viewangle>>ANGLETOFINESHIFT];
	
    sscount = 0;
	
    if (player->fixedcolormap)
    {
	fixedcolormap =
	    colormaps
	    + player->fixedcolormap*256*sizeof(lighttable_t);
	
	walllights = scalelightfixed;

	for (i=0 ; i<MAXLIGHTSCALE ; i++)
	    scalelightfixed[i] = fixedcolormap;
    }
    else
	fixedcolormap = 0;
		
    framecount++;
    validcount++;
}