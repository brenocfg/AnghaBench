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
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  programname ; 

__attribute__((used)) static void usage(void)
{
    die("\n"
	"Usage: %s [options] <filename>\n"
	"\n"
	"Valid options:\n"
	"    -h          : display this usage information\n"
	"    -n <name>   : specify logo name (default: linux_logo)\n"
	"    -o <output> : output to file <output> instead of stdout\n"
	"    -t <type>   : specify logo type, one of\n"
	"                      mono    : monochrome black/white\n"
	"                      vga16   : 16 colors VGA text palette\n"
	"                      clut224 : 224 colors (default)\n"
	"                      gray256 : 256 levels grayscale\n"
	"\n", programname);
}