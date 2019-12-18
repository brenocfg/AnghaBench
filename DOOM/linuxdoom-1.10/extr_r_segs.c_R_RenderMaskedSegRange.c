#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int scalestep; int scale1; int x1; int /*<<< orphan*/  sprtopclip; int /*<<< orphan*/  sprbottomclip; scalar_t__* maskedtexturecol; TYPE_7__* curline; } ;
typedef  TYPE_5__ drawseg_t ;
typedef  int /*<<< orphan*/  column_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_17__ {scalar_t__ floorheight; scalar_t__ ceilingheight; } ;
struct TYPE_16__ {TYPE_4__* sidedef; TYPE_3__* linedef; TYPE_2__* v2; TYPE_1__* v1; TYPE_8__* backsector; TYPE_6__* frontsector; } ;
struct TYPE_15__ {int lightlevel; scalar_t__ floorheight; scalar_t__ ceilingheight; } ;
struct TYPE_13__ {size_t midtexture; scalar_t__ rowoffset; } ;
struct TYPE_12__ {int flags; } ;
struct TYPE_11__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_10__ {scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 scalar_t__ FixedMul (scalar_t__,int) ; 
 int LIGHTLEVELS ; 
 int LIGHTSCALESHIFT ; 
 int LIGHTSEGSHIFT ; 
 unsigned int MAXLIGHTSCALE ; 
 scalar_t__ MAXSHORT ; 
 int ML_DONTPEGBOTTOM ; 
 int /*<<< orphan*/  R_DrawMaskedColumn (int /*<<< orphan*/ *) ; 
 scalar_t__ R_GetColumn (int,scalar_t__) ; 
 TYPE_8__* backsector ; 
 scalar_t__ centeryfrac ; 
 TYPE_7__* curline ; 
 scalar_t__ dc_colormap ; 
 int dc_iscale ; 
 scalar_t__ dc_texturemid ; 
 int dc_x ; 
 int extralight ; 
 scalar_t__ fixedcolormap ; 
 TYPE_6__* frontsector ; 
 scalar_t__* maskedtexturecol ; 
 int /*<<< orphan*/  mceilingclip ; 
 int /*<<< orphan*/  mfloorclip ; 
 int rw_scalestep ; 
 scalar_t__** scalelight ; 
 scalar_t__ sprtopscreen ; 
 int spryscale ; 
 scalar_t__* textureheight ; 
 int* texturetranslation ; 
 scalar_t__ viewz ; 
 scalar_t__* walllights ; 

void
R_RenderMaskedSegRange
( drawseg_t*	ds,
  int		x1,
  int		x2 )
{
    unsigned	index;
    column_t*	col;
    int		lightnum;
    int		texnum;
    
    // Calculate light table.
    // Use different light tables
    //   for horizontal / vertical / diagonal. Diagonal?
    // OPTIMIZE: get rid of LIGHTSEGSHIFT globally
    curline = ds->curline;
    frontsector = curline->frontsector;
    backsector = curline->backsector;
    texnum = texturetranslation[curline->sidedef->midtexture];
	
    lightnum = (frontsector->lightlevel >> LIGHTSEGSHIFT)+extralight;

    if (curline->v1->y == curline->v2->y)
	lightnum--;
    else if (curline->v1->x == curline->v2->x)
	lightnum++;

    if (lightnum < 0)		
	walllights = scalelight[0];
    else if (lightnum >= LIGHTLEVELS)
	walllights = scalelight[LIGHTLEVELS-1];
    else
	walllights = scalelight[lightnum];

    maskedtexturecol = ds->maskedtexturecol;

    rw_scalestep = ds->scalestep;		
    spryscale = ds->scale1 + (x1 - ds->x1)*rw_scalestep;
    mfloorclip = ds->sprbottomclip;
    mceilingclip = ds->sprtopclip;
    
    // find positioning
    if (curline->linedef->flags & ML_DONTPEGBOTTOM)
    {
	dc_texturemid = frontsector->floorheight > backsector->floorheight
	    ? frontsector->floorheight : backsector->floorheight;
	dc_texturemid = dc_texturemid + textureheight[texnum] - viewz;
    }
    else
    {
	dc_texturemid =frontsector->ceilingheight<backsector->ceilingheight
	    ? frontsector->ceilingheight : backsector->ceilingheight;
	dc_texturemid = dc_texturemid - viewz;
    }
    dc_texturemid += curline->sidedef->rowoffset;
			
    if (fixedcolormap)
	dc_colormap = fixedcolormap;
    
    // draw the columns
    for (dc_x = x1 ; dc_x <= x2 ; dc_x++)
    {
	// calculate lighting
	if (maskedtexturecol[dc_x] != MAXSHORT)
	{
	    if (!fixedcolormap)
	    {
		index = spryscale>>LIGHTSCALESHIFT;

		if (index >=  MAXLIGHTSCALE )
		    index = MAXLIGHTSCALE-1;

		dc_colormap = walllights[index];
	    }
			
	    sprtopscreen = centeryfrac - FixedMul(dc_texturemid, spryscale);
	    dc_iscale = 0xffffffffu / (unsigned)spryscale;
	    
	    // draw the texture
	    col = (column_t *)( 
		(byte *)R_GetColumn(texnum,maskedtexturecol[dc_x]) -3);
			
	    R_DrawMaskedColumn (col);
	    maskedtexturecol[dc_x] = MAXSHORT;
	}
	spryscale += rw_scalestep;
    }
	
}