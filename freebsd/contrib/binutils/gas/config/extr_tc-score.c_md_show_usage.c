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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void
md_show_usage (FILE * fp)
{
  fprintf (fp, _(" Score-specific assembler options:\n"));
#ifdef OPTION_EB
  fprintf (fp, _("\
        -EB\t\tassemble code for a big-endian cpu\n"));
#endif

#ifdef OPTION_EL
  fprintf (fp, _("\
        -EL\t\tassemble code for a little-endian cpu\n"));
#endif

  fprintf (fp, _("\
        -FIXDD\t\tassemble code for fix data dependency\n"));
  fprintf (fp, _("\
        -NWARN\t\tassemble code for no warning message for fix data dependency\n"));
  fprintf (fp, _("\
        -SCORE5\t\tassemble code for target is SCORE5\n"));
  fprintf (fp, _("\
        -SCORE5U\tassemble code for target is SCORE5U\n"));
  fprintf (fp, _("\
        -SCORE7\t\tassemble code for target is SCORE7, this is default setting\n"));
  fprintf (fp, _("\
        -USE_R1\t\tassemble code for no warning message when using temp register r1\n"));
  fprintf (fp, _("\
        -KPIC\t\tassemble code for PIC\n"));
  fprintf (fp, _("\
        -O0\t\tassembler will not perform any optimizations\n"));
  fprintf (fp, _("\
        -G gpnum\tassemble code for setting gpsize and default is 8 byte\n"));
  fprintf (fp, _("\
        -V \t\tSunplus release version \n"));
}