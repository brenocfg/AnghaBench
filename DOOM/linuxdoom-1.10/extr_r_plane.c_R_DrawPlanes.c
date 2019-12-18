#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int minx; int maxx; size_t picnum; scalar_t__* top; scalar_t__* bottom; int lightlevel; scalar_t__ height; } ;
typedef  TYPE_1__ visplane_t ;

/* Variables and functions */
 int ANGLETOSKYSHIFT ; 
 int /*<<< orphan*/  I_Error (char*,scalar_t__) ; 
 int LIGHTLEVELS ; 
 int LIGHTSEGSHIFT ; 
 scalar_t__ MAXDRAWSEGS ; 
 scalar_t__ MAXOPENINGS ; 
 int MAXVISPLANES ; 
 int /*<<< orphan*/  PU_CACHE ; 
 int /*<<< orphan*/  PU_STATIC ; 
 int /*<<< orphan*/  R_GetColumn (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  R_MakeSpans (int,int,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  W_CacheLumpNum (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ChangeTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abs (scalar_t__) ; 
 int /*<<< orphan*/  colfunc () ; 
 int /*<<< orphan*/  colormaps ; 
 int /*<<< orphan*/  dc_colormap ; 
 int dc_iscale ; 
 int /*<<< orphan*/  dc_source ; 
 int /*<<< orphan*/  dc_texturemid ; 
 int dc_x ; 
 scalar_t__ dc_yh ; 
 scalar_t__ dc_yl ; 
 int detailshift ; 
 scalar_t__ drawsegs ; 
 scalar_t__ ds_p ; 
 int /*<<< orphan*/  ds_source ; 
 int extralight ; 
 scalar_t__ firstflat ; 
 scalar_t__* flattranslation ; 
 scalar_t__ lastopening ; 
 TYPE_1__* lastvisplane ; 
 scalar_t__ openings ; 
 int /*<<< orphan*/  planeheight ; 
 int /*<<< orphan*/  planezlight ; 
 int pspriteiscale ; 
 size_t skyflatnum ; 
 int /*<<< orphan*/  skytexture ; 
 int /*<<< orphan*/  skytexturemid ; 
 int viewangle ; 
 scalar_t__ viewz ; 
 TYPE_1__* visplanes ; 
 int* xtoviewangle ; 
 int /*<<< orphan*/ * zlight ; 

void R_DrawPlanes (void)
{
    visplane_t*		pl;
    int			light;
    int			x;
    int			stop;
    int			angle;
				
#ifdef RANGECHECK
    if (ds_p - drawsegs > MAXDRAWSEGS)
	I_Error ("R_DrawPlanes: drawsegs overflow (%i)",
		 ds_p - drawsegs);
    
    if (lastvisplane - visplanes > MAXVISPLANES)
	I_Error ("R_DrawPlanes: visplane overflow (%i)",
		 lastvisplane - visplanes);
    
    if (lastopening - openings > MAXOPENINGS)
	I_Error ("R_DrawPlanes: opening overflow (%i)",
		 lastopening - openings);
#endif

    for (pl = visplanes ; pl < lastvisplane ; pl++)
    {
	if (pl->minx > pl->maxx)
	    continue;

	
	// sky flat
	if (pl->picnum == skyflatnum)
	{
	    dc_iscale = pspriteiscale>>detailshift;
	    
	    // Sky is allways drawn full bright,
	    //  i.e. colormaps[0] is used.
	    // Because of this hack, sky is not affected
	    //  by INVUL inverse mapping.
	    dc_colormap = colormaps;
	    dc_texturemid = skytexturemid;
	    for (x=pl->minx ; x <= pl->maxx ; x++)
	    {
		dc_yl = pl->top[x];
		dc_yh = pl->bottom[x];

		if (dc_yl <= dc_yh)
		{
		    angle = (viewangle + xtoviewangle[x])>>ANGLETOSKYSHIFT;
		    dc_x = x;
		    dc_source = R_GetColumn(skytexture, angle);
		    colfunc ();
		}
	    }
	    continue;
	}
	
	// regular flat
	ds_source = W_CacheLumpNum(firstflat +
				   flattranslation[pl->picnum],
				   PU_STATIC);
	
	planeheight = abs(pl->height-viewz);
	light = (pl->lightlevel >> LIGHTSEGSHIFT)+extralight;

	if (light >= LIGHTLEVELS)
	    light = LIGHTLEVELS-1;

	if (light < 0)
	    light = 0;

	planezlight = zlight[light];

	pl->top[pl->maxx+1] = 0xff;
	pl->top[pl->minx-1] = 0xff;
		
	stop = pl->maxx + 1;

	for (x=pl->minx ; x<= stop ; x++)
	{
	    R_MakeSpans(x,pl->top[x-1],
			pl->bottom[x-1],
			pl->top[x],
			pl->bottom[x]);
	}
	
	Z_ChangeTag (ds_source, PU_CACHE);
    }
}