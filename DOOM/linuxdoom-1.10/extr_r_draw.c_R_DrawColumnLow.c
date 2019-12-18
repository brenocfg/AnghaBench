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
typedef  size_t fixed_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 size_t FRACBITS ; 
 int /*<<< orphan*/  I_Error (char*,size_t,scalar_t__,int) ; 
 scalar_t__ SCREENHEIGHT ; 
 unsigned int SCREENWIDTH ; 
 size_t centery ; 
 int* columnofs ; 
 int /*<<< orphan*/ * dc_colormap ; 
 size_t dc_iscale ; 
 size_t* dc_source ; 
 size_t dc_texturemid ; 
 int dc_x ; 
 scalar_t__ dc_yh ; 
 size_t dc_yl ; 
 int /*<<< orphan*/ ** ylookup ; 

void R_DrawColumnLow (void) 
{ 
    int			count; 
    byte*		dest; 
    byte*		dest2;
    fixed_t		frac;
    fixed_t		fracstep;	 
 
    count = dc_yh - dc_yl; 

    // Zero length.
    if (count < 0) 
	return; 
				 
#ifdef RANGECHECK 
    if ((unsigned)dc_x >= SCREENWIDTH
	|| dc_yl < 0
	|| dc_yh >= SCREENHEIGHT)
    {
	
	I_Error ("R_DrawColumn: %i to %i at %i", dc_yl, dc_yh, dc_x);
    }
    //	dccount++; 
#endif 
    // Blocky mode, need to multiply by 2.
    dc_x <<= 1;
    
    dest = ylookup[dc_yl] + columnofs[dc_x];
    dest2 = ylookup[dc_yl] + columnofs[dc_x+1];
    
    fracstep = dc_iscale; 
    frac = dc_texturemid + (dc_yl-centery)*fracstep;
    
    do 
    {
	// Hack. Does not work corretly.
	*dest2 = *dest = dc_colormap[dc_source[(frac>>FRACBITS)&127]];
	dest += SCREENWIDTH;
	dest2 += SCREENWIDTH;
	frac += fracstep; 

    } while (count--);
}