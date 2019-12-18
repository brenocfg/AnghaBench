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
 int indent ; 
 int /*<<< orphan*/ * outfile ; 
 int /*<<< orphan*/  print_rtx (int /*<<< orphan*/ ) ; 
 int sawclose ; 

void
print_inline_rtx (FILE *outf, rtx x, int ind)
{
  int oldsaw = sawclose;
  int oldindent = indent;

  sawclose = 0;
  indent = ind;
  outfile = outf;
  print_rtx (x);
  sawclose = oldsaw;
  indent = oldindent;
}