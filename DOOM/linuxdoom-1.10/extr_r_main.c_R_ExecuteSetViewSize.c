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
typedef  int fixed_t ;

/* Variables and functions */
 size_t ANGLETOFINESHIFT ; 
 int DISTMAP ; 
 int FRACBITS ; 
 int FRACUNIT ; 
 void* FixedDiv (int,int) ; 
 int LIGHTLEVELS ; 
 int MAXLIGHTSCALE ; 
 int NUMCOLORMAPS ; 
 int /*<<< orphan*/  R_DrawColumn ; 
 int /*<<< orphan*/  R_DrawColumnLow ; 
 int /*<<< orphan*/  R_DrawFuzzColumn ; 
 int /*<<< orphan*/  R_DrawSpan ; 
 int /*<<< orphan*/  R_DrawSpanLow ; 
 int /*<<< orphan*/  R_DrawTranslatedColumn ; 
 int /*<<< orphan*/  R_InitBuffer (int,int) ; 
 int /*<<< orphan*/  R_InitTextureMapping () ; 
 int SCREENHEIGHT ; 
 int SCREENWIDTH ; 
 int abs (int) ; 
 int /*<<< orphan*/  basecolfunc ; 
 int centerx ; 
 int centerxfrac ; 
 int centery ; 
 int centeryfrac ; 
 int /*<<< orphan*/  colfunc ; 
 scalar_t__ colormaps ; 
 int detailshift ; 
 void** distscale ; 
 int* finecosine ; 
 int /*<<< orphan*/  fuzzcolfunc ; 
 int projection ; 
 int pspriteiscale ; 
 int pspritescale ; 
 int scaledviewwidth ; 
 scalar_t__** scalelight ; 
 int* screenheightarray ; 
 int setblocks ; 
 int setdetail ; 
 int setsizeneeded ; 
 int /*<<< orphan*/  spanfunc ; 
 int /*<<< orphan*/  transcolfunc ; 
 int viewheight ; 
 int viewwidth ; 
 size_t* xtoviewangle ; 
 void** yslope ; 

void R_ExecuteSetViewSize (void)
{
    fixed_t	cosadj;
    fixed_t	dy;
    int		i;
    int		j;
    int		level;
    int		startmap; 	

    setsizeneeded = false;

    if (setblocks == 11)
    {
	scaledviewwidth = SCREENWIDTH;
	viewheight = SCREENHEIGHT;
    }
    else
    {
	scaledviewwidth = setblocks*32;
	viewheight = (setblocks*168/10)&~7;
    }
    
    detailshift = setdetail;
    viewwidth = scaledviewwidth>>detailshift;
	
    centery = viewheight/2;
    centerx = viewwidth/2;
    centerxfrac = centerx<<FRACBITS;
    centeryfrac = centery<<FRACBITS;
    projection = centerxfrac;

    if (!detailshift)
    {
	colfunc = basecolfunc = R_DrawColumn;
	fuzzcolfunc = R_DrawFuzzColumn;
	transcolfunc = R_DrawTranslatedColumn;
	spanfunc = R_DrawSpan;
    }
    else
    {
	colfunc = basecolfunc = R_DrawColumnLow;
	fuzzcolfunc = R_DrawFuzzColumn;
	transcolfunc = R_DrawTranslatedColumn;
	spanfunc = R_DrawSpanLow;
    }

    R_InitBuffer (scaledviewwidth, viewheight);
	
    R_InitTextureMapping ();
    
    // psprite scales
    pspritescale = FRACUNIT*viewwidth/SCREENWIDTH;
    pspriteiscale = FRACUNIT*SCREENWIDTH/viewwidth;
    
    // thing clipping
    for (i=0 ; i<viewwidth ; i++)
	screenheightarray[i] = viewheight;
    
    // planes
    for (i=0 ; i<viewheight ; i++)
    {
	dy = ((i-viewheight/2)<<FRACBITS)+FRACUNIT/2;
	dy = abs(dy);
	yslope[i] = FixedDiv ( (viewwidth<<detailshift)/2*FRACUNIT, dy);
    }
	
    for (i=0 ; i<viewwidth ; i++)
    {
	cosadj = abs(finecosine[xtoviewangle[i]>>ANGLETOFINESHIFT]);
	distscale[i] = FixedDiv (FRACUNIT,cosadj);
    }
    
    // Calculate the light levels to use
    //  for each level / scale combination.
    for (i=0 ; i< LIGHTLEVELS ; i++)
    {
	startmap = ((LIGHTLEVELS-1-i)*2)*NUMCOLORMAPS/LIGHTLEVELS;
	for (j=0 ; j<MAXLIGHTSCALE ; j++)
	{
	    level = startmap - j*SCREENWIDTH/(viewwidth<<detailshift)/DISTMAP;
	    
	    if (level < 0)
		level = 0;

	    if (level >= NUMCOLORMAPS)
		level = NUMCOLORMAPS-1;

	    scalelight[i][j] = colormaps + level*256;
	}
    }
}