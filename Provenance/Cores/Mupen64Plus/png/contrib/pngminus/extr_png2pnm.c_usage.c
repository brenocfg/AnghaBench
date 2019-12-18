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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void usage()
{
  fprintf (stderr, "PNG2PNM\n");
  fprintf (stderr, "   by Willem van Schaik, 1999\n");
#ifdef __TURBOC__
  fprintf (stderr, "   for Turbo-C and Borland-C compilers\n");
#else
  fprintf (stderr, "   for Linux (and Unix) compilers\n");
#endif
  fprintf (stderr, "Usage:  png2pnm [options] <file>.png [<file>.pnm]\n");
  fprintf (stderr, "   or:  ... | png2pnm [options]\n");
  fprintf (stderr, "Options:\n");
  fprintf (stderr,
     "   -r[aw]   write pnm-file in binary format (P4/P5/P6) (default)\n");
  fprintf (stderr, "   -n[oraw] write pnm-file in ascii format (P1/P2/P3)\n");
  fprintf (stderr,
     "   -a[lpha] <file>.pgm write PNG alpha channel as pgm-file\n");
  fprintf (stderr, "   -h | -?  print this help-information\n");
}