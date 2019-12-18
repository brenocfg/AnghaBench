#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct change {scalar_t__ line0; scalar_t__ deleted; scalar_t__ inserted; scalar_t__ line1; struct change* link; } ;
typedef  scalar_t__ lin ;
typedef  enum changes { ____Placeholder_changes } changes ;
struct TYPE_5__ {scalar_t__ fastmap; } ;
struct TYPE_4__ {scalar_t__ prefix_lines; scalar_t__ valid_lines; int /*<<< orphan*/ * linbuf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int NEW ; 
 int OLD ; 
 int analyze_hunk (struct change*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  begin_output () ; 
 scalar_t__ context ; 
 TYPE_1__* files ; 
 char* find_function (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ function_regexp ; 
 int /*<<< orphan*/ * outfile ; 
 int /*<<< orphan*/  print_1_line (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_context_function (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  print_context_number_range (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
pr_context_hunk (struct change *hunk)
{
  lin first0, last0, first1, last1, i;
  char const *prefix;
  char const *function;
  FILE *out;

  /* Determine range of line numbers involved in each file.  */

  enum changes changes = analyze_hunk (hunk, &first0, &last0, &first1, &last1);
  if (! changes)
    return;

  /* Include a context's width before and after.  */

  i = - files[0].prefix_lines;
  first0 = MAX (first0 - context, i);
  first1 = MAX (first1 - context, i);
  if (last0 < files[0].valid_lines - context)
    last0 += context;
  else
    last0 = files[0].valid_lines - 1;
  if (last1 < files[1].valid_lines - context)
    last1 += context;
  else
    last1 = files[1].valid_lines - 1;

  /* If desired, find the preceding function definition line in file 0.  */
  function = 0;
  if (function_regexp.fastmap)
    function = find_function (files[0].linbuf, first0);

  begin_output ();
  out = outfile;

  fprintf (out, "***************");

  if (function)
    print_context_function (out, function);

  fprintf (out, "\n*** ");
  print_context_number_range (&files[0], first0, last0);
  fprintf (out, " ****\n");

  if (changes & OLD)
    {
      struct change *next = hunk;

      for (i = first0; i <= last0; i++)
	{
	  /* Skip past changes that apply (in file 0)
	     only to lines before line I.  */

	  while (next && next->line0 + next->deleted <= i)
	    next = next->link;

	  /* Compute the marking for line I.  */

	  prefix = " ";
	  if (next && next->line0 <= i)
	    /* The change NEXT covers this line.
	       If lines were inserted here in file 1, this is "changed".
	       Otherwise it is "deleted".  */
	    prefix = (next->inserted > 0 ? "!" : "-");

	  print_1_line (prefix, &files[0].linbuf[i]);
	}
    }

  fprintf (out, "--- ");
  print_context_number_range (&files[1], first1, last1);
  fprintf (out, " ----\n");

  if (changes & NEW)
    {
      struct change *next = hunk;

      for (i = first1; i <= last1; i++)
	{
	  /* Skip past changes that apply (in file 1)
	     only to lines before line I.  */

	  while (next && next->line1 + next->inserted <= i)
	    next = next->link;

	  /* Compute the marking for line I.  */

	  prefix = " ";
	  if (next && next->line1 <= i)
	    /* The change NEXT covers this line.
	       If lines were deleted here in file 0, this is "changed".
	       Otherwise it is "inserted".  */
	    prefix = (next->deleted > 0 ? "!" : "+");

	  print_1_line (prefix, &files[1].linbuf[i]);
	}
    }
}