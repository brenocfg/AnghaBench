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
typedef  int /*<<< orphan*/  snes_ntsc_t ;
typedef  int /*<<< orphan*/  snes_ntsc_out_t ;
typedef  int /*<<< orphan*/  SNES_NTSC_IN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SNES_NTSC_ADJ_IN (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  SNES_NTSC_COLOR_IN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNES_NTSC_HIRES_OUT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNES_NTSC_HIRES_ROW (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNES_NTSC_OUT_DEPTH ; 
 int /*<<< orphan*/  snes_ntsc_black ; 
 int snes_ntsc_burst_count ; 
 int snes_ntsc_in_chunk ; 

void retroarch_snes_ntsc_blit_hires( snes_ntsc_t const* ntsc, SNES_NTSC_IN_T const* input, long in_row_width,
		int burst_phase, int in_width, int in_height, void* rgb_out, long out_pitch, int first, int last )
{
	int chunk_count = (in_width - 2) / (snes_ntsc_in_chunk * 2);
	for ( ; in_height; --in_height )
	{
		SNES_NTSC_IN_T const* line_in = input;
		SNES_NTSC_HIRES_ROW( ntsc, burst_phase,
				snes_ntsc_black, snes_ntsc_black, snes_ntsc_black,
				SNES_NTSC_ADJ_IN( line_in [0] ),
				SNES_NTSC_ADJ_IN( line_in [1] ) );
		snes_ntsc_out_t* line_out = (snes_ntsc_out_t*) rgb_out;
		int n;
		line_in += 2;

		for ( n = chunk_count; n; --n )
		{
			/* twice as many input pixels per chunk */
			SNES_NTSC_COLOR_IN( 0, SNES_NTSC_ADJ_IN( line_in [0] ) );
			SNES_NTSC_HIRES_OUT( 0, line_out [0], SNES_NTSC_OUT_DEPTH );

			SNES_NTSC_COLOR_IN( 1, SNES_NTSC_ADJ_IN( line_in [1] ) );
			SNES_NTSC_HIRES_OUT( 1, line_out [1], SNES_NTSC_OUT_DEPTH );

			SNES_NTSC_COLOR_IN( 2, SNES_NTSC_ADJ_IN( line_in [2] ) );
			SNES_NTSC_HIRES_OUT( 2, line_out [2], SNES_NTSC_OUT_DEPTH );

			SNES_NTSC_COLOR_IN( 3, SNES_NTSC_ADJ_IN( line_in [3] ) );
			SNES_NTSC_HIRES_OUT( 3, line_out [3], SNES_NTSC_OUT_DEPTH );

			SNES_NTSC_COLOR_IN( 4, SNES_NTSC_ADJ_IN( line_in [4] ) );
			SNES_NTSC_HIRES_OUT( 4, line_out [4], SNES_NTSC_OUT_DEPTH );

			SNES_NTSC_COLOR_IN( 5, SNES_NTSC_ADJ_IN( line_in [5] ) );
			SNES_NTSC_HIRES_OUT( 5, line_out [5], SNES_NTSC_OUT_DEPTH );
			SNES_NTSC_HIRES_OUT( 6, line_out [6], SNES_NTSC_OUT_DEPTH );

			line_in  += 6;
			line_out += 7;
		}

		SNES_NTSC_COLOR_IN( 0, snes_ntsc_black );
		SNES_NTSC_HIRES_OUT( 0, line_out [0], SNES_NTSC_OUT_DEPTH );

		SNES_NTSC_COLOR_IN( 1, snes_ntsc_black );
		SNES_NTSC_HIRES_OUT( 1, line_out [1], SNES_NTSC_OUT_DEPTH );

		SNES_NTSC_COLOR_IN( 2, snes_ntsc_black );
		SNES_NTSC_HIRES_OUT( 2, line_out [2], SNES_NTSC_OUT_DEPTH );

		SNES_NTSC_COLOR_IN( 3, snes_ntsc_black );
		SNES_NTSC_HIRES_OUT( 3, line_out [3], SNES_NTSC_OUT_DEPTH );

		SNES_NTSC_COLOR_IN( 4, snes_ntsc_black );
		SNES_NTSC_HIRES_OUT( 4, line_out [4], SNES_NTSC_OUT_DEPTH );

		SNES_NTSC_COLOR_IN( 5, snes_ntsc_black );
		SNES_NTSC_HIRES_OUT( 5, line_out [5], SNES_NTSC_OUT_DEPTH );
		SNES_NTSC_HIRES_OUT( 6, line_out [6], SNES_NTSC_OUT_DEPTH );

		burst_phase = (burst_phase + 1) % snes_ntsc_burst_count;
		input += in_row_width;
		rgb_out = (char*) rgb_out + out_pitch;
	}
}