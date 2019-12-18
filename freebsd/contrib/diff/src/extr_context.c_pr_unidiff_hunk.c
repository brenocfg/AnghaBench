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
struct change {scalar_t__ line0; scalar_t__ deleted; scalar_t__ inserted; struct change* link; } ;
typedef  scalar_t__ lin ;
struct TYPE_5__ {scalar_t__ fastmap; } ;
struct TYPE_4__ {scalar_t__ prefix_lines; scalar_t__ valid_lines; int /*<<< orphan*/ * linbuf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  analyze_hunk (struct change*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  begin_output () ; 
 scalar_t__ context ; 
 TYPE_1__* files ; 
 char* find_function (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ function_regexp ; 
 scalar_t__ initial_tab ; 
 int /*<<< orphan*/ * outfile ; 
 int /*<<< orphan*/  print_1_line (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_context_function (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  print_unidiff_number_range (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pr_unidiff_hunk (struct change *hunk)
{
  lin first0, last0, first1, last1;
  lin i, j, k;
  struct change *next;
  char const *function;
  FILE *out;

  /* Determine range of line numbers involved in each file.  */

  if (! analyze_hunk (hunk, &first0, &last0, &first1, &last1))
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

  fprintf (out, "@@ -");
  print_unidiff_number_range (&files[0], first0, last0);
  fprintf (out, " +");
  print_unidiff_number_range (&files[1], first1, last1);
  fprintf (out, " @@");

  if (function)
    print_context_function (out, function);

  putc ('\n', out);

  next = hunk;
  i = first0;
  j = first1;

  while (i <= last0 || j <= last1)
    {

      /* If the line isn't a difference, output the context from file 0. */

      if (!next || i < next->line0)
	{
	  putc (initial_tab ? '\t' : ' ', out);
	  print_1_line (0, &files[0].linbuf[i++]);
	  j++;
	}
      else
	{
	  /* For each difference, first output the deleted part. */

	  k = next->deleted;
	  while (k--)
	    {
	      putc ('-', out);
	      if (initial_tab)
		putc ('\t', out);
	      print_1_line (0, &files[0].linbuf[i++]);
	    }

	  /* Then output the inserted part. */

	  k = next->inserted;
	  while (k--)
	    {
	      putc ('+', out);
	      if (initial_tab)
		putc ('\t', out);
	      print_1_line (0, &files[1].linbuf[j++]);
	    }

	  /* We're done with this hunk, so on to the next! */

	  next = next->link;
	}
    }
}