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
typedef  int /*<<< orphan*/  nes_ntsc_t ;
typedef  int /*<<< orphan*/  nes_ntsc_out_t ;
typedef  int /*<<< orphan*/  NES_NTSC_IN_T ;

/* Variables and functions */
 int /*<<< orphan*/  NES_NTSC_ADJ_IN (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  NES_NTSC_BEGIN_ROW (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NES_NTSC_COLOR_IN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NES_NTSC_RGB_OUT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutputDepth ; 
 int /*<<< orphan*/  nes_ntsc_black ; 
 int nes_ntsc_burst_count ; 
 int nes_ntsc_in_chunk ; 
 int /*<<< orphan*/  rescale_out ; 

void nes_ntsc_blit( nes_ntsc_t const* ntsc, NES_NTSC_IN_T const* input, long in_row_width,
		int burst_phase, int emphasis, int in_width, int in_height, void* rgb_out, long out_pitch )
{
	int chunk_count = (in_width - 1) / nes_ntsc_in_chunk;

	for ( ; in_height; --in_height )
	{
		NES_NTSC_IN_T const* line_in = input;
		NES_NTSC_BEGIN_ROW( ntsc, burst_phase, nes_ntsc_black, nes_ntsc_black, NES_NTSC_ADJ_IN( *line_in ) );
		nes_ntsc_out_t* restrict line_out = (nes_ntsc_out_t*) rgb_out;
		int n;
		++line_in;

		for ( n = chunk_count; n; --n )
		{

			/* order of input and output pixels must not be altered */
			NES_NTSC_COLOR_IN( 0, NES_NTSC_ADJ_IN( line_in [0] ) );
			NES_NTSC_RGB_OUT( 0, line_out [0], OutputDepth );
			NES_NTSC_RGB_OUT( 1, line_out [1], OutputDepth );
			
			NES_NTSC_COLOR_IN( 1, NES_NTSC_ADJ_IN( line_in [1] ) );
			NES_NTSC_RGB_OUT( 2, line_out [2], OutputDepth );
			NES_NTSC_RGB_OUT( 3, line_out [3], OutputDepth );
			
			NES_NTSC_COLOR_IN( 2, NES_NTSC_ADJ_IN( line_in [2] ) );
			NES_NTSC_RGB_OUT( 4, line_out [4], OutputDepth );
			NES_NTSC_RGB_OUT( 5, line_out [5], OutputDepth );
			NES_NTSC_RGB_OUT( 6, line_out [6], OutputDepth );
			
			line_in  += 3;
			line_out += rescale_out;
		}
		
		/* finish final pixels */
		NES_NTSC_COLOR_IN( 0, nes_ntsc_black );
		NES_NTSC_RGB_OUT( 0, line_out [0], OutputDepth );
		NES_NTSC_RGB_OUT( 1, line_out [1], OutputDepth );
		
		NES_NTSC_COLOR_IN( 1, nes_ntsc_black );
		NES_NTSC_RGB_OUT( 2, line_out [2], OutputDepth );
		NES_NTSC_RGB_OUT( 3, line_out [3], OutputDepth );
		
		NES_NTSC_COLOR_IN( 2, nes_ntsc_black );
		NES_NTSC_RGB_OUT( 4, line_out [4], OutputDepth );
		NES_NTSC_RGB_OUT( 5, line_out [5], OutputDepth );
		NES_NTSC_RGB_OUT( 6, line_out [6], OutputDepth );
		rgb_out = (char*) rgb_out + out_pitch;
		
		burst_phase = (burst_phase + 1) % nes_ntsc_burst_count;
		input += in_row_width;
	}
}