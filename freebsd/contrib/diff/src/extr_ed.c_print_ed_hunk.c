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
struct TYPE_3__ {char** linbuf; } ;

/* Variables and functions */
 int OLD ; 
 int analyze_hunk (struct change*,size_t*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  begin_output () ; 
 int* change_letter ; 
 int /*<<< orphan*/  debug_script (struct change*) ; 
 TYPE_1__* files ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  print_1_line (char*,char**) ; 
 int /*<<< orphan*/  print_number_range (char,TYPE_1__*,size_t,size_t) ; 

__attribute__((used)) static void
print_ed_hunk (struct change *hunk)
{
  lin f0, l0, f1, l1;
  enum changes changes;

#ifdef DEBUG
  debug_script (hunk);
#endif

  /* Determine range of line numbers involved in each file.  */
  changes = analyze_hunk (hunk, &f0, &l0, &f1, &l1);
  if (!changes)
    return;

  begin_output ();

  /* Print out the line number header for this hunk */
  print_number_range (',', &files[0], f0, l0);
  fprintf (outfile, "%c\n", change_letter[changes]);

  /* Print new/changed lines from second file, if needed */
  if (changes != OLD)
    {
      lin i;
      for (i = f1; i <= l1; i++)
	{
	  if (files[1].linbuf[i][0] == '.' && files[1].linbuf[i][1] == '\n')
	    {
	      /* The file's line is just a dot, and it would exit
		 insert mode.  Precede the dot with another dot, exit
		 insert mode, remove the extra dot, and then resume
		 insert mode.  */
	      fprintf (outfile, "..\n.\ns/.//\na\n");
	    }
	  else
	    print_1_line ("", &files[1].linbuf[i]);
	}

      fprintf (outfile, ".\n");
    }
}