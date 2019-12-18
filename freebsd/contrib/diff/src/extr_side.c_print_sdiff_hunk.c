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
struct change {int dummy; } ;
typedef  int lin ;
typedef  enum changes { ____Placeholder_changes } changes ;
struct TYPE_2__ {int /*<<< orphan*/ * linbuf; } ;

/* Variables and functions */
 int CHANGED ; 
 int NEW ; 
 int OLD ; 
 int analyze_hunk (struct change*,int*,int*,int*,int*) ; 
 TYPE_1__* files ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,long) ; 
 int next0 ; 
 int next1 ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  print_1sdiff_line (int /*<<< orphan*/ *,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_sdiff_common_lines (int,int) ; 
 scalar_t__ sdiff_merge_assist ; 

__attribute__((used)) static void
print_sdiff_hunk (struct change *hunk)
{
  lin first0, last0, first1, last1;
  register lin i, j;

  /* Determine range of line numbers involved in each file.  */
  enum changes changes =
    analyze_hunk (hunk, &first0, &last0, &first1, &last1);
  if (!changes)
    return;

  /* Print out lines up to this change.  */
  print_sdiff_common_lines (first0, first1);

  if (sdiff_merge_assist)
    {
      long int len0 = last0 - first0 + 1;
      long int len1 = last1 - first1 + 1;
      fprintf (outfile, "c%ld,%ld\n", len0, len1);
    }

  /* Print ``xxx  |  xxx '' lines */
  if (changes == CHANGED)
    {
      for (i = first0, j = first1;  i <= last0 && j <= last1;  i++, j++)
	print_1sdiff_line (&files[0].linbuf[i], '|', &files[1].linbuf[j]);
      changes = (i <= last0 ? OLD : 0) + (j <= last1 ? NEW : 0);
      next0 = first0 = i;
      next1 = first1 = j;
    }

  /* Print ``     >  xxx '' lines */
  if (changes & NEW)
    {
      for (j = first1; j <= last1; ++j)
	print_1sdiff_line (0, '>', &files[1].linbuf[j]);
      next1 = j;
    }

  /* Print ``xxx  <     '' lines */
  if (changes & OLD)
    {
      for (i = first0; i <= last0; ++i)
	print_1sdiff_line (&files[0].linbuf[i], '<', 0);
      next0 = i;
    }
}