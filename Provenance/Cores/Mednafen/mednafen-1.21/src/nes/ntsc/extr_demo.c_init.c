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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (unsigned char*,long,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ nes_height ; 
 int /*<<< orphan*/  nes_ntsc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* nes_pixels ; 
 long nes_width ; 
 int /*<<< orphan*/ * ntsc ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static void init()
{
	/* read raw image */
	FILE* file = fopen( "nes.raw", "rb" );
	if ( !file )
		fatal_error( "Couldn't open image file" );
	nes_pixels = (unsigned char*) malloc( (long) nes_height * nes_width );
	if ( !nes_pixels )
		fatal_error( "Out of memory" );
	fread( nes_pixels, nes_width, nes_height, file );
	fclose( file );
	
	/* allocate memory for nes_ntsc and initialize */
	ntsc = (nes_ntsc_t*) malloc( sizeof (nes_ntsc_t) );
	if ( !ntsc )
		fatal_error( "Out of memory" );
	nes_ntsc_init( ntsc, &setup );
}