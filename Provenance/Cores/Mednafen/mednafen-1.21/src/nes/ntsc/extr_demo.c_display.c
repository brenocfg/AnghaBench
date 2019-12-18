#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ merge_fields; } ;

/* Variables and functions */
 int burst_phase ; 
 int /*<<< orphan*/  nes_height ; 
 int /*<<< orphan*/  nes_ntsc_blit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  nes_pixels ; 
 int /*<<< orphan*/  nes_width ; 
 int /*<<< orphan*/  ntsc ; 
 int out_height ; 
 int out_width ; 
 int /*<<< orphan*/  sdl_display () ; 
 int /*<<< orphan*/  sdl_lock_pixels () ; 
 int sdl_pitch ; 
 unsigned char* sdl_pixels ; 
 TYPE_1__ setup ; 

__attribute__((used)) static void display()
{
	sdl_lock_pixels();
	
	/* force phase to 0 if merge_fields is on */
	burst_phase ^= 1;
	if ( setup.merge_fields )
		burst_phase = 0;
	
	/* blit image to every other row of output by doubling output pitch */
	nes_ntsc_blit( ntsc, nes_pixels, nes_width, burst_phase,
			nes_width, nes_height, sdl_pixels, sdl_pitch * 2 );
	
	/* interpolate and darken between scanlines */
	{
		int y;
		for ( y = 1; y < out_height - 1; y += 2 )
		{
			unsigned char* io = sdl_pixels + y * sdl_pitch;
			int n;
			for ( n = out_width; n; --n )
			{
				unsigned prev = *(unsigned short*) (io - sdl_pitch);
				unsigned next = *(unsigned short*) (io + sdl_pitch);
				/* mix 16-bit rgb without losing low bits */
				unsigned mixed = prev + next + ((prev ^ next) & 0x0821);
				/* darken by 12% */
				*(unsigned short*) io = (mixed >> 1) - (mixed >> 4 & 0x18E3);
				io += 2;
			}
		}
	}
	
	sdl_display();
}