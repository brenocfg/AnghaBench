#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lin ;
struct TYPE_2__ {int /*<<< orphan*/ * linbuf; } ;

/* Variables and functions */
 TYPE_1__* files ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,long) ; 
 int /*<<< orphan*/  left_column ; 
 scalar_t__ next0 ; 
 scalar_t__ next1 ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  print_1sdiff_line (int /*<<< orphan*/ *,char,int /*<<< orphan*/ *) ; 
 scalar_t__ sdiff_merge_assist ; 
 int /*<<< orphan*/  suppress_common_lines ; 

__attribute__((used)) static void
print_sdiff_common_lines (lin limit0, lin limit1)
{
  lin i0 = next0, i1 = next1;

  if (!suppress_common_lines && (i0 != limit0 || i1 != limit1))
    {
      if (sdiff_merge_assist)
	{
	  long int len0 = limit0 - i0;
	  long int len1 = limit1 - i1;
	  fprintf (outfile, "i%ld,%ld\n", len0, len1);
	}

      if (!left_column)
	{
	  while (i0 != limit0 && i1 != limit1)
	    print_1sdiff_line (&files[0].linbuf[i0++], ' ',
			       &files[1].linbuf[i1++]);
	  while (i1 != limit1)
	    print_1sdiff_line (0, ')', &files[1].linbuf[i1++]);
	}
      while (i0 != limit0)
	print_1sdiff_line (&files[0].linbuf[i0++], '(', 0);
    }

  next0 = limit0;
  next1 = limit1;
}