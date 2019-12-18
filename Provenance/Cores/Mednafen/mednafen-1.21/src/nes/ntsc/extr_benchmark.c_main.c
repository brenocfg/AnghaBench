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
struct data_t {int** in; int /*<<< orphan*/ * out; int /*<<< orphan*/  ntsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct data_t*) ; 
 int in_height ; 
 int in_width ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  nes_ntsc_blit (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nes_ntsc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rand () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ time_blitter () ; 

int main()
{
	struct data_t* data = (struct data_t*) malloc( sizeof *data );
	if ( data )
	{
		/* fill with random pixel data */
		int y;
		for ( y = 0; y < in_height; y++ )
		{
			int x;
			for ( x = 0; x < in_width; x++ )
				data->in [y] [x] = rand() >> 4 & 0x1F;
		}
		
		printf( "Timing nes_ntsc...\n" );
		fflush( stdout );
		
		nes_ntsc_init( &data->ntsc, 0 );
		
		/* measure frame rate */
		while ( time_blitter() )
		{
			nes_ntsc_blit( &data->ntsc, data->in [0], in_width, 0,
				in_width, in_height, data->out [0], sizeof data->out [0] );
		}
		
		free( data );
	}
	
	return 0;
}