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
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ NOTE_LINE_NUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_dump_unnumbered ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * outfile ; 
 int /*<<< orphan*/  print_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rtx_head ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 scalar_t__ sawclose ; 

int
print_rtl_single (FILE *outf, rtx x)
{
  outfile = outf;
  sawclose = 0;
  if (! flag_dump_unnumbered
      || !NOTE_P (x) || NOTE_LINE_NUMBER (x) < 0)
    {
      fputs (print_rtx_head, outfile);
      print_rtx (x);
      putc ('\n', outf);
      return 1;
    }
  return 0;
}