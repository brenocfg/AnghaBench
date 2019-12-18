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

/* Variables and functions */
 char* DriverUsage ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 

void ShowUsage(char *prog)
{
printf("\nUsage is as follows:\n%s <options> filename\n\n",prog);
puts("Options:");
puts(DriverUsage);
puts("-cpalette x     Load a custom global palette from file x.\n\
-ntsccol x      Emulate an NTSC's TV's colors.\n\
                 0 = Disabled.\n\
                 1 = Enabled.\n\
-pal x          Emulate a PAL NES if x is 1.\n\
-sound x        Sound.\n\
                 0 = Disabled.\n\
                 Otherwise, x = playback rate.\n\
-soundvol x	Sound volume. x is an integral percentage value.\n\
-soundq x	Sets sound quality.\n\
		 0 = Low quality.\n\
		 1 = High quality.\n\
-inputx str	Select device mapped to virtual input port x(1-2).\n\
		 str may be: none, gamepad, zapper, powerpada, powerpadb,\n\
			     arkanoid\n\
-fcexp str	Select Famicom expansion port device.\n\
		 str may be: none, shadow, arkanoid, 4player, fkb\n\
-inputcfg s	Configure virtual input device \"s\".\n\
-nofs x		Disables Four-Score emulation if x is 1.\n\
-gg x           Enable Game Genie emulation if x is 1.\n\
-no8lim x       Disables the 8 sprites per scanline limitation.\n\
                 0 = Limitation enabled.\n\
                 1 = Limitation disabled.\n\
-snapname x	Selects what type of file name snapshots will have.\n\
		 0 = Numeric(0.png)\n\
		 1 = File base and numeric(mario-0.png)\n\
-nothrottle x	Disable artificial speed throttling if x is non-zero.\n\
-clipsides x	Clip leftmost and rightmost 8 columns of pixels of video output.\n\
                 0 = No clipping.\n\
                 1 = Clipping.\n\
-slstart x	Set the first drawn emulated scanline.  Valid values for x are\n\
	        0 through 239.\n\
-slend x	Set the last drawn emulated scanline.  Valid values for x are\n\
		0 through 239.");
}