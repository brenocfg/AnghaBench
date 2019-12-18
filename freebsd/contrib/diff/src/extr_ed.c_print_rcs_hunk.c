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
struct change {int dummy; } ;
typedef  size_t lin ;
typedef  enum changes { ____Placeholder_changes } changes ;
struct TYPE_3__ {int /*<<< orphan*/ * linbuf; } ;

/* Variables and functions */
 int NEW ; 
 int OLD ; 
 int analyze_hunk (struct change*,size_t*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  begin_output () ; 
 TYPE_1__* files ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  print_1_line (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  translate_range (TYPE_1__*,size_t,size_t,long*,long*) ; 

__attribute__((used)) static void
print_rcs_hunk (struct change *hunk)
{
  lin i, f0, l0, f1, l1;
  long int tf0, tl0, tf1, tl1;

  /* Determine range of line numbers involved in each file.  */
  enum changes changes = analyze_hunk (hunk, &f0, &l0, &f1, &l1);
  if (!changes)
    return;

  begin_output ();

  translate_range (&files[0], f0, l0, &tf0, &tl0);

  if (changes & OLD)
    {
      fprintf (outfile, "d");
      /* For deletion, print just the starting line number from file 0
	 and the number of lines deleted.  */
      fprintf (outfile, "%ld %ld\n", tf0, tf0 <= tl0 ? tl0 - tf0 + 1 : 1);
    }

  if (changes & NEW)
    {
      fprintf (outfile, "a");

      /* Take last-line-number from file 0 and # lines from file 1.  */
      translate_range (&files[1], f1, l1, &tf1, &tl1);
      fprintf (outfile, "%ld %ld\n", tl0, tf1 <= tl1 ? tl1 - tf1 + 1 : 1);

      /* Print the inserted lines.  */
      for (i = f1; i <= l1; i++)
	print_1_line ("", &files[1].linbuf[i]);
    }
}