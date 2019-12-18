#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ state; } ;
typedef  TYPE_4__ pspdef_t ;
struct TYPE_11__ {TYPE_4__* psprites; TYPE_2__* mo; } ;
struct TYPE_9__ {TYPE_1__* sector; } ;
struct TYPE_8__ {TYPE_3__* subsector; } ;
struct TYPE_7__ {int lightlevel; } ;

/* Variables and functions */
 int LIGHTLEVELS ; 
 int LIGHTSEGSHIFT ; 
 int NUMPSPRITES ; 
 int /*<<< orphan*/  R_DrawPSprite (TYPE_4__*) ; 
 int extralight ; 
 int /*<<< orphan*/  mceilingclip ; 
 int /*<<< orphan*/  mfloorclip ; 
 int /*<<< orphan*/  negonearray ; 
 int /*<<< orphan*/ * scalelight ; 
 int /*<<< orphan*/  screenheightarray ; 
 int /*<<< orphan*/  spritelights ; 
 TYPE_5__* viewplayer ; 

void R_DrawPlayerSprites (void)
{
    int		i;
    int		lightnum;
    pspdef_t*	psp;
    
    // get light level
    lightnum =
	(viewplayer->mo->subsector->sector->lightlevel >> LIGHTSEGSHIFT) 
	+extralight;

    if (lightnum < 0)		
	spritelights = scalelight[0];
    else if (lightnum >= LIGHTLEVELS)
	spritelights = scalelight[LIGHTLEVELS-1];
    else
	spritelights = scalelight[lightnum];
    
    // clip to screen bounds
    mfloorclip = screenheightarray;
    mceilingclip = negonearray;
    
    // add all active psprites
    for (i=0, psp=viewplayer->psprites;
	 i<NUMPSPRITES;
	 i++,psp++)
    {
	if (psp->state)
	    R_DrawPSprite (psp);
    }
}