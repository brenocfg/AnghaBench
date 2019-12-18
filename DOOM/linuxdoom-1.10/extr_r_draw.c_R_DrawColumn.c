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
 int /*<<< orphan*/  I_Error (char*,size_t,scalar_t__,size_t) ; 
 scalar_t__ SCREENHEIGHT ; 
 unsigned int SCREENWIDTH ; 
 size_t centery ; 
 int* columnofs ; 
 int /*<<< orphan*/ * dc_colormap ; 
 size_t dc_iscale ; 
 size_t* dc_source ; 
 size_t dc_texturemid ; 
 size_t dc_x ; 
 scalar_t__ dc_yh ; 
 size_t dc_yl ; 
 int /*<<< orphan*/ ** ylookup ; 

void R_DrawColumn (void) 
{ 
    int			count; 
    byte*		dest; 
    fixed_t		frac;
    fixed_t		fracstep;	 
 
    count = dc_yh - dc_yl; 

    // Zero length, column does not exceed a pixel.
    if (count < 0) 
	return; 
				 
#ifdef RANGECHECK 
    if ((unsigned)dc_x >= SCREENWIDTH
	|| dc_yl < 0
	|| dc_yh >= SCREENHEIGHT) 
	I_Error ("R_DrawColumn: %i to %i at %i", dc_yl, dc_yh, dc_x); 
#endif 

    // Framebuffer destination address.
    // Use ylookup LUT to avoid multiply with ScreenWidth.
    // Use columnofs LUT for subwindows? 
    dest = ylookup[dc_yl] + columnofs[dc_x];  

    // Determine scaling,
    //  which is the only mapping to be done.
    fracstep = dc_iscale; 
    frac = dc_texturemid + (dc_yl-centery)*fracstep; 

    // Inner loop that does the actual texture mapping,
    //  e.g. a DDA-lile scaling.
    // This is as fast as it gets.
    do 
    {
	// Re-map color indices from wall texture column
	//  using a lighting/special effects LUT.
	*dest = dc_colormap[dc_source[(frac>>FRACBITS)&127]];
	
	dest += SCREENWIDTH; 
	frac += fracstep;
	
    } while (count--); 
}