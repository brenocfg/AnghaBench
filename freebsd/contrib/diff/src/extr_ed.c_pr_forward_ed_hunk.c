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
pr_forward_ed_hunk (struct change *hunk)
{
  lin i, f0, l0, f1, l1;

  /* Determine range of line numbers involved in each file.  */
  enum changes changes = analyze_hunk (hunk, &f0, &l0, &f1, &l1);
  if (!changes)
    return;

  begin_output ();

  fprintf (outfile, "%c", change_letter[changes]);
  print_number_range (' ', files, f0, l0);
  fprintf (outfile, "\n");

  /* If deletion only, print just the number range.  */

  if (changes == OLD)
    return;

  /* For insertion (with or without deletion), print the number range
     and the lines from file 2.  */

  for (i = f1; i <= l1; i++)
    print_1_line ("", &files[1].linbuf[i]);

  fprintf (outfile, ".\n");
}