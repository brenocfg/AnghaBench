#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* palette_out; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_ntsc_init (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ setup ; 

__attribute__((used)) static void write_palette()
{
	FILE* out = fopen( "nes.pal", "wb" );
	if ( out )
	{
		unsigned char palette [64 * 3];
		setup.palette_out = palette;
		nes_ntsc_init( 0, &setup );
		fwrite( palette, sizeof palette, 1, out );
	}
}