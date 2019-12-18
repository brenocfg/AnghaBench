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
 int CHANGED ; 
 int NEW ; 
 int OLD ; 
 int analyze_hunk (struct change*,size_t*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  begin_output () ; 
 int* change_letter ; 
 TYPE_1__* files ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  print_1_line (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_number_range (char,TYPE_1__*,size_t,size_t) ; 

__attribute__((used)) static void
print_normal_hunk (struct change *hunk)
{
  lin first0, last0, first1, last1;
  register lin i;

  /* Determine range of line numbers involved in each file.  */
  enum changes changes = analyze_hunk (hunk, &first0, &last0, &first1, &last1);
  if (!changes)
    return;

  begin_output ();

  /* Print out the line number header for this hunk */
  print_number_range (',', &files[0], first0, last0);
  fprintf (outfile, "%c", change_letter[changes]);
  print_number_range (',', &files[1], first1, last1);
  fprintf (outfile, "\n");

  /* Print the lines that the first file has.  */
  if (changes & OLD)
    for (i = first0; i <= last0; i++)
      print_1_line ("<", &files[0].linbuf[i]);

  if (changes == CHANGED)
    fprintf (outfile, "---\n");

  /* Print the lines that the second file has.  */
  if (changes & NEW)
    for (i = first1; i <= last1; i++)
      print_1_line (">", &files[1].linbuf[i]);
}