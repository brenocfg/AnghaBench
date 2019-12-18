#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float sharpness; float hue_warping; int merge_fields; float* decoder_matrix; scalar_t__ hue; } ;

/* Variables and functions */
#define  SDLK_SPACE 133 
#define  SDLK_c 132 
#define  SDLK_d 131 
#define  SDLK_m 130 
#define  SDLK_r 129 
#define  SDLK_s 128 
 int /*<<< orphan*/  display () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init () ; 
 int key_pressed ; 
 scalar_t__ mouse_moved ; 
 int mouse_x ; 
 int mouse_y ; 
 TYPE_1__ nes_ntsc_composite ; 
 int /*<<< orphan*/  nes_ntsc_init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ nes_ntsc_monochrome ; 
 TYPE_1__ nes_ntsc_rgb ; 
 TYPE_1__ nes_ntsc_svideo ; 
 int /*<<< orphan*/  ntsc ; 
 int /*<<< orphan*/  out_height ; 
 int /*<<< orphan*/  out_width ; 
 int /*<<< orphan*/  sdl_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sdl_run () ; 
 TYPE_1__ setup ; 
 int /*<<< orphan*/  write_palette () ; 

int main( int argc, char** argv )
{
	int merge_fields = 1;
	int sony_decoder = 0;
	
	setup = nes_ntsc_composite;
	init();
	sdl_init( out_width, out_height, 16 ); /* 16-bit RGB output buffer */
	
	/* keep displaying frames until mouse is clicked */
	while ( sdl_run() )
	{
		display();
		
		switch ( key_pressed )
		{
			case SDLK_SPACE: merge_fields = !merge_fields; break;
			
			case SDLK_c    : setup = nes_ntsc_composite; break;
			
			case SDLK_s    : setup = nes_ntsc_svideo; break;
			
			case SDLK_r    : setup = nes_ntsc_rgb; break;
			
			case SDLK_m    : setup = nes_ntsc_monochrome; break;
			
			case SDLK_d    : sony_decoder = !sony_decoder; break;
		}
		
		if ( key_pressed || mouse_moved )
		{
			/* convert mouse range to -1 to +1 */
			float x = mouse_x * 2 - 1;
			float y = mouse_y * 2 - 1;
			
			/* parameters: hue, saturation, contrast, brightness, sharpness,
			gamma, bleed, resolution, artifacts, fringing, hue_warping */
			setup.sharpness   = x;
			setup.hue_warping = y;
			
			setup.merge_fields = merge_fields;
			
			setup.decoder_matrix = 0;
			setup.hue = 0;
			if ( sony_decoder )
			{
				/* Sony CXA2095S US */
				static float matrix [6] = { 1.539, -0.622, -0.571, -0.185, 0.000, 2.000 };
				setup.decoder_matrix = matrix;
				setup.hue += 33 / 180.0;
			}
			
			nes_ntsc_init( ntsc, &setup );
		}
	}
	
	free( ntsc );
	
	write_palette();
	
	return 0;
}