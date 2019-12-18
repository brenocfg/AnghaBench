#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int mobjflags; int scale; int gx; int gy; int x1; int x2; int xiscale; int patch; int /*<<< orphan*/ * colormap; scalar_t__ startfrac; scalar_t__ gzt; scalar_t__ texturemid; scalar_t__ gz; } ;
typedef  TYPE_1__ vissprite_t ;
struct TYPE_9__ {int* lump; scalar_t__* flip; scalar_t__ rotate; } ;
typedef  TYPE_2__ spriteframe_t ;
struct TYPE_10__ {size_t numframes; TYPE_2__* spriteframes; } ;
typedef  TYPE_3__ spritedef_t ;
struct TYPE_11__ {int x; int y; size_t sprite; size_t frame; unsigned int angle; int flags; scalar_t__ z; } ;
typedef  TYPE_4__ mobj_t ;
typedef  int fixed_t ;
typedef  scalar_t__ boolean ;
typedef  unsigned int angle_t ;

/* Variables and functions */
 int ANG45 ; 
 size_t FF_FRAMEMASK ; 
 int FF_FULLBRIGHT ; 
 int FRACBITS ; 
 int /*<<< orphan*/  FRACUNIT ; 
 int FixedDiv (int /*<<< orphan*/ ,int) ; 
 int FixedMul (int,int) ; 
 int /*<<< orphan*/  I_Error (char*,size_t,...) ; 
 int LIGHTSCALESHIFT ; 
 int MAXLIGHTSCALE ; 
 int MF_SHADOW ; 
 int MINZ ; 
 TYPE_1__* R_NewVisSprite () ; 
 unsigned int R_PointToAngle (int,int) ; 
 int abs (int) ; 
 int centerxfrac ; 
 int /*<<< orphan*/ * colormaps ; 
 int detailshift ; 
 int /*<<< orphan*/ * fixedcolormap ; 
 unsigned int numsprites ; 
 int /*<<< orphan*/  projection ; 
 int /*<<< orphan*/ ** spritelights ; 
 scalar_t__* spriteoffset ; 
 TYPE_3__* sprites ; 
 scalar_t__* spritetopoffset ; 
 scalar_t__* spritewidth ; 
 int viewcos ; 
 int viewsin ; 
 int viewwidth ; 
 int viewx ; 
 int viewy ; 
 scalar_t__ viewz ; 

void R_ProjectSprite (mobj_t* thing)
{
    fixed_t		tr_x;
    fixed_t		tr_y;
    
    fixed_t		gxt;
    fixed_t		gyt;
    
    fixed_t		tx;
    fixed_t		tz;

    fixed_t		xscale;
    
    int			x1;
    int			x2;

    spritedef_t*	sprdef;
    spriteframe_t*	sprframe;
    int			lump;
    
    unsigned		rot;
    boolean		flip;
    
    int			index;

    vissprite_t*	vis;
    
    angle_t		ang;
    fixed_t		iscale;
    
    // transform the origin point
    tr_x = thing->x - viewx;
    tr_y = thing->y - viewy;
	
    gxt = FixedMul(tr_x,viewcos); 
    gyt = -FixedMul(tr_y,viewsin);
    
    tz = gxt-gyt; 

    // thing is behind view plane?
    if (tz < MINZ)
	return;
    
    xscale = FixedDiv(projection, tz);
	
    gxt = -FixedMul(tr_x,viewsin); 
    gyt = FixedMul(tr_y,viewcos); 
    tx = -(gyt+gxt); 

    // too far off the side?
    if (abs(tx)>(tz<<2))
	return;
    
    // decide which patch to use for sprite relative to player
#ifdef RANGECHECK
    if ((unsigned)thing->sprite >= numsprites)
	I_Error ("R_ProjectSprite: invalid sprite number %i ",
		 thing->sprite);
#endif
    sprdef = &sprites[thing->sprite];
#ifdef RANGECHECK
    if ( (thing->frame&FF_FRAMEMASK) >= sprdef->numframes )
	I_Error ("R_ProjectSprite: invalid sprite frame %i : %i ",
		 thing->sprite, thing->frame);
#endif
    sprframe = &sprdef->spriteframes[ thing->frame & FF_FRAMEMASK];

    if (sprframe->rotate)
    {
	// choose a different rotation based on player view
	ang = R_PointToAngle (thing->x, thing->y);
	rot = (ang-thing->angle+(unsigned)(ANG45/2)*9)>>29;
	lump = sprframe->lump[rot];
	flip = (boolean)sprframe->flip[rot];
    }
    else
    {
	// use single rotation for all views
	lump = sprframe->lump[0];
	flip = (boolean)sprframe->flip[0];
    }
    
    // calculate edges of the shape
    tx -= spriteoffset[lump];	
    x1 = (centerxfrac + FixedMul (tx,xscale) ) >>FRACBITS;

    // off the right side?
    if (x1 > viewwidth)
	return;
    
    tx +=  spritewidth[lump];
    x2 = ((centerxfrac + FixedMul (tx,xscale) ) >>FRACBITS) - 1;

    // off the left side
    if (x2 < 0)
	return;
    
    // store information in a vissprite
    vis = R_NewVisSprite ();
    vis->mobjflags = thing->flags;
    vis->scale = xscale<<detailshift;
    vis->gx = thing->x;
    vis->gy = thing->y;
    vis->gz = thing->z;
    vis->gzt = thing->z + spritetopoffset[lump];
    vis->texturemid = vis->gzt - viewz;
    vis->x1 = x1 < 0 ? 0 : x1;
    vis->x2 = x2 >= viewwidth ? viewwidth-1 : x2;	
    iscale = FixedDiv (FRACUNIT, xscale);

    if (flip)
    {
	vis->startfrac = spritewidth[lump]-1;
	vis->xiscale = -iscale;
    }
    else
    {
	vis->startfrac = 0;
	vis->xiscale = iscale;
    }

    if (vis->x1 > x1)
	vis->startfrac += vis->xiscale*(vis->x1-x1);
    vis->patch = lump;
    
    // get light level
    if (thing->flags & MF_SHADOW)
    {
	// shadow draw
	vis->colormap = NULL;
    }
    else if (fixedcolormap)
    {
	// fixed map
	vis->colormap = fixedcolormap;
    }
    else if (thing->frame & FF_FULLBRIGHT)
    {
	// full bright
	vis->colormap = colormaps;
    }
    
    else
    {
	// diminished light
	index = xscale>>(LIGHTSCALESHIFT-detailshift);

	if (index >= MAXLIGHTSCALE) 
	    index = MAXLIGHTSCALE-1;

	vis->colormap = spritelights[index];
    }	
}