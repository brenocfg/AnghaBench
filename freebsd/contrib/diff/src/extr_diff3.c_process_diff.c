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
struct diff_block {struct diff_block* next; int /*<<< orphan*/ ** lengths; int /*<<< orphan*/ ** lines; int /*<<< orphan*/ ** ranges; } ;
typedef  size_t lin ;
typedef  enum diff_type { ____Placeholder_diff_type } diff_type ;

/* Variables and functions */
#define  ADD 130 
#define  CHANGE 129 
#define  DELETE 128 
 size_t D_NUMLINES (struct diff_block*,int) ; 
 int ERROR ; 
 int /*<<< orphan*/  EXIT_TROUBLE ; 
 size_t MIN (int,int) ; 
 size_t PTRDIFF_MAX ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int process_diff_control (char**,struct diff_block*) ; 
 char* program_name ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 char* read_diff (char const*,char const*,char**) ; 
 char* scan_diff_line (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  xalloc_die () ; 
 void* xmalloc (size_t) ; 

__attribute__((used)) static struct diff_block *
process_diff (char const *filea,
	      char const *fileb,
	      struct diff_block **last_block)
{
  char *diff_contents;
  char *diff_limit;
  char *scan_diff;
  enum diff_type dt;
  lin i;
  struct diff_block *block_list, **block_list_end, *bptr;
  size_t too_many_lines = (PTRDIFF_MAX
			   / MIN (sizeof *bptr->lines[1],
				  sizeof *bptr->lengths[1]));

  diff_limit = read_diff (filea, fileb, &diff_contents);
  scan_diff = diff_contents;
  block_list_end = &block_list;
  bptr = 0; /* Pacify `gcc -W'.  */

  while (scan_diff < diff_limit)
    {
      bptr = xmalloc (sizeof *bptr);
      bptr->lines[0] = bptr->lines[1] = 0;
      bptr->lengths[0] = bptr->lengths[1] = 0;

      dt = process_diff_control (&scan_diff, bptr);
      if (dt == ERROR || *scan_diff != '\n')
	{
	  fprintf (stderr, _("%s: diff failed: "), program_name);
	  do
	    {
	      putc (*scan_diff, stderr);
	    }
	  while (*scan_diff++ != '\n');
	  exit (EXIT_TROUBLE);
	}
      scan_diff++;

      /* Force appropriate ranges to be null, if necessary */
      switch (dt)
	{
	case ADD:
	  bptr->ranges[0][0]++;
	  break;
	case DELETE:
	  bptr->ranges[1][0]++;
	  break;
	case CHANGE:
	  break;
	default:
	  fatal ("internal error: invalid diff type in process_diff");
	  break;
	}

      /* Allocate space for the pointers for the lines from filea, and
	 parcel them out among these pointers */
      if (dt != ADD)
	{
	  lin numlines = D_NUMLINES (bptr, 0);
	  if (too_many_lines <= numlines)
	    xalloc_die ();
	  bptr->lines[0] = xmalloc (numlines * sizeof *bptr->lines[0]);
	  bptr->lengths[0] = xmalloc (numlines * sizeof *bptr->lengths[0]);
	  for (i = 0; i < numlines; i++)
	    scan_diff = scan_diff_line (scan_diff,
					&(bptr->lines[0][i]),
					&(bptr->lengths[0][i]),
					diff_limit,
					'<');
	}

      /* Get past the separator for changes */
      if (dt == CHANGE)
	{
	  if (strncmp (scan_diff, "---\n", 4))
	    fatal ("invalid diff format; invalid change separator");
	  scan_diff += 4;
	}

      /* Allocate space for the pointers for the lines from fileb, and
	 parcel them out among these pointers */
      if (dt != DELETE)
	{
	  lin numlines = D_NUMLINES (bptr, 1);
	  if (too_many_lines <= numlines)
	    xalloc_die ();
	  bptr->lines[1] = xmalloc (numlines * sizeof *bptr->lines[1]);
	  bptr->lengths[1] = xmalloc (numlines * sizeof *bptr->lengths[1]);
	  for (i = 0; i < numlines; i++)
	    scan_diff = scan_diff_line (scan_diff,
					&(bptr->lines[1][i]),
					&(bptr->lengths[1][i]),
					diff_limit,
					'>');
	}

      /* Place this block on the blocklist.  */
      *block_list_end = bptr;
      block_list_end = &bptr->next;
    }

  *block_list_end = 0;
  *last_block = bptr;
  return block_list;
}