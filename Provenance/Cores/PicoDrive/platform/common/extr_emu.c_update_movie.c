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
struct TYPE_3__ {int frame_count; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 int* PicoPad ; 
 int /*<<< orphan*/  emu_status_msg (char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  lprintf (char*) ; 
 int* movie_data ; 
 int movie_size ; 

__attribute__((used)) static void update_movie(void)
{
	int offs = Pico.m.frame_count*3 + 0x40;
	if (offs+3 > movie_size) {
		free(movie_data);
		movie_data = 0;
		emu_status_msg("END OF MOVIE.");
		lprintf("END OF MOVIE.\n");
	} else {
		// MXYZ SACB RLDU
		PicoPad[0] = ~movie_data[offs]   & 0x8f; // ! SCBA RLDU
		if(!(movie_data[offs]   & 0x10)) PicoPad[0] |= 0x40; // C
		if(!(movie_data[offs]   & 0x20)) PicoPad[0] |= 0x10; // A
		if(!(movie_data[offs]   & 0x40)) PicoPad[0] |= 0x20; // B
		PicoPad[1] = ~movie_data[offs+1] & 0x8f; // ! SCBA RLDU
		if(!(movie_data[offs+1] & 0x10)) PicoPad[1] |= 0x40; // C
		if(!(movie_data[offs+1] & 0x20)) PicoPad[1] |= 0x10; // A
		if(!(movie_data[offs+1] & 0x40)) PicoPad[1] |= 0x20; // B
		PicoPad[0] |= (~movie_data[offs+2] & 0x0A) << 8; // ! MZYX
		if(!(movie_data[offs+2] & 0x01)) PicoPad[0] |= 0x0400; // X
		if(!(movie_data[offs+2] & 0x04)) PicoPad[0] |= 0x0100; // Z
		PicoPad[1] |= (~movie_data[offs+2] & 0xA0) << 4; // ! MZYX
		if(!(movie_data[offs+2] & 0x10)) PicoPad[1] |= 0x0400; // X
		if(!(movie_data[offs+2] & 0x40)) PicoPad[1] |= 0x0100; // Z
	}
}