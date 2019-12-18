#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int fixed_t ;
typedef  size_t angle_t ;
struct TYPE_4__ {int* top; int* bottom; } ;
struct TYPE_3__ {int* top; int* bottom; } ;

/* Variables and functions */
 size_t ANGLETOFINESHIFT ; 
 int FRACBITS ; 
 int FixedMul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HEIGHTBITS ; 
 int HEIGHTUNIT ; 
 unsigned int LIGHTSCALESHIFT ; 
 unsigned int MAXLIGHTSCALE ; 
 int /*<<< orphan*/  R_GetColumn (scalar_t__,int) ; 
 int bottomfrac ; 
 scalar_t__ bottomstep ; 
 scalar_t__ bottomtexture ; 
 int* ceilingclip ; 
 TYPE_2__* ceilingplane ; 
 int /*<<< orphan*/  colfunc () ; 
 int /*<<< orphan*/  dc_colormap ; 
 int dc_iscale ; 
 int /*<<< orphan*/  dc_source ; 
 int /*<<< orphan*/  dc_texturemid ; 
 size_t dc_x ; 
 int dc_yh ; 
 int dc_yl ; 
 int /*<<< orphan*/ * finetangent ; 
 int* floorclip ; 
 TYPE_1__* floorplane ; 
 scalar_t__ markceiling ; 
 scalar_t__ markfloor ; 
 scalar_t__ maskedtexture ; 
 int* maskedtexturecol ; 
 scalar_t__ midtexture ; 
 int pixhigh ; 
 scalar_t__ pixhighstep ; 
 int pixlow ; 
 scalar_t__ pixlowstep ; 
 int /*<<< orphan*/  rw_bottomtexturemid ; 
 size_t rw_centerangle ; 
 int /*<<< orphan*/  rw_distance ; 
 int /*<<< orphan*/  rw_midtexturemid ; 
 int rw_offset ; 
 unsigned int rw_scale ; 
 scalar_t__ rw_scalestep ; 
 size_t rw_stopx ; 
 int /*<<< orphan*/  rw_toptexturemid ; 
 size_t rw_x ; 
 scalar_t__ segtextured ; 
 int topfrac ; 
 scalar_t__ topstep ; 
 scalar_t__ toptexture ; 
 int viewheight ; 
 int /*<<< orphan*/ * walllights ; 
 size_t* xtoviewangle ; 

void R_RenderSegLoop (void)
{
    angle_t		angle;
    unsigned		index;
    int			yl;
    int			yh;
    int			mid;
    fixed_t		texturecolumn;
    int			top;
    int			bottom;

    //texturecolumn = 0;				// shut up compiler warning
	
    for ( ; rw_x < rw_stopx ; rw_x++)
    {
	// mark floor / ceiling areas
	yl = (topfrac+HEIGHTUNIT-1)>>HEIGHTBITS;

	// no space above wall?
	if (yl < ceilingclip[rw_x]+1)
	    yl = ceilingclip[rw_x]+1;
	
	if (markceiling)
	{
	    top = ceilingclip[rw_x]+1;
	    bottom = yl-1;

	    if (bottom >= floorclip[rw_x])
		bottom = floorclip[rw_x]-1;

	    if (top <= bottom)
	    {
		ceilingplane->top[rw_x] = top;
		ceilingplane->bottom[rw_x] = bottom;
	    }
	}
		
	yh = bottomfrac>>HEIGHTBITS;

	if (yh >= floorclip[rw_x])
	    yh = floorclip[rw_x]-1;

	if (markfloor)
	{
	    top = yh+1;
	    bottom = floorclip[rw_x]-1;
	    if (top <= ceilingclip[rw_x])
		top = ceilingclip[rw_x]+1;
	    if (top <= bottom)
	    {
		floorplane->top[rw_x] = top;
		floorplane->bottom[rw_x] = bottom;
	    }
	}
	
	// texturecolumn and lighting are independent of wall tiers
	if (segtextured)
	{
	    // calculate texture offset
	    angle = (rw_centerangle + xtoviewangle[rw_x])>>ANGLETOFINESHIFT;
	    texturecolumn = rw_offset-FixedMul(finetangent[angle],rw_distance);
	    texturecolumn >>= FRACBITS;
	    // calculate lighting
	    index = rw_scale>>LIGHTSCALESHIFT;

	    if (index >=  MAXLIGHTSCALE )
		index = MAXLIGHTSCALE-1;

	    dc_colormap = walllights[index];
	    dc_x = rw_x;
	    dc_iscale = 0xffffffffu / (unsigned)rw_scale;
	}
	
	// draw the wall tiers
	if (midtexture)
	{
	    // single sided line
	    dc_yl = yl;
	    dc_yh = yh;
	    dc_texturemid = rw_midtexturemid;
	    dc_source = R_GetColumn(midtexture,texturecolumn);
	    colfunc ();
	    ceilingclip[rw_x] = viewheight;
	    floorclip[rw_x] = -1;
	}
	else
	{
	    // two sided line
	    if (toptexture)
	    {
		// top wall
		mid = pixhigh>>HEIGHTBITS;
		pixhigh += pixhighstep;

		if (mid >= floorclip[rw_x])
		    mid = floorclip[rw_x]-1;

		if (mid >= yl)
		{
		    dc_yl = yl;
		    dc_yh = mid;
		    dc_texturemid = rw_toptexturemid;
		    dc_source = R_GetColumn(toptexture,texturecolumn);
		    colfunc ();
		    ceilingclip[rw_x] = mid;
		}
		else
		    ceilingclip[rw_x] = yl-1;
	    }
	    else
	    {
		// no top wall
		if (markceiling)
		    ceilingclip[rw_x] = yl-1;
	    }
			
	    if (bottomtexture)
	    {
		// bottom wall
		mid = (pixlow+HEIGHTUNIT-1)>>HEIGHTBITS;
		pixlow += pixlowstep;

		// no space above wall?
		if (mid <= ceilingclip[rw_x])
		    mid = ceilingclip[rw_x]+1;
		
		if (mid <= yh)
		{
		    dc_yl = mid;
		    dc_yh = yh;
		    dc_texturemid = rw_bottomtexturemid;
		    dc_source = R_GetColumn(bottomtexture,
					    texturecolumn);
		    colfunc ();
		    floorclip[rw_x] = mid;
		}
		else
		    floorclip[rw_x] = yh+1;
	    }
	    else
	    {
		// no bottom wall
		if (markfloor)
		    floorclip[rw_x] = yh+1;
	    }
			
	    if (maskedtexture)
	    {
		// save texturecol
		//  for backdrawing of masked mid texture
		maskedtexturecol[rw_x] = texturecolumn;
	    }
	}
		
	rw_scale += rw_scalestep;
	topfrac += topstep;
	bottomfrac += bottomstep;
    }
}