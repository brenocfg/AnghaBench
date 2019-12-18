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
struct macro_source_file {int included_at_line; struct macro_source_file* next_included; struct macro_source_file* included_by; int /*<<< orphan*/  table; int /*<<< orphan*/  filename; struct macro_source_file* includes; } ;

/* Variables and functions */
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct macro_source_file* new_source_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  symfile_complaints ; 

struct macro_source_file *
macro_include (struct macro_source_file *source,
               int line,
               const char *included)
{
  struct macro_source_file *new;
  struct macro_source_file **link;

  /* Find the right position in SOURCE's `includes' list for the new
     file.  Skip inclusions at earlier lines, until we find one at the
     same line or later --- or until the end of the list.  */
  for (link = &source->includes;
       *link && (*link)->included_at_line < line;
       link = &(*link)->next_included)
    ;

  /* Did we find another file already #included at the same line as
     the new one?  */
  if (*link && line == (*link)->included_at_line)
    {
      /* This means the compiler is emitting bogus debug info.  (GCC
         circa March 2002 did this.)  It also means that the splay
         tree ordering function, macro_tree_compare, will abort,
         because it can't tell which #inclusion came first.  But GDB
         should tolerate bad debug info.  So:

         First, squawk.  */
      complaint (&symfile_complaints,
		 "both `%s' and `%s' allegedly #included at %s:%d", included,
		 (*link)->filename, source->filename, line);

      /* Now, choose a new, unoccupied line number for this
         #inclusion, after the alleged #inclusion line.  */
      while (*link && line == (*link)->included_at_line)
        {
          /* This line number is taken, so try the next line.  */
          line++;
          link = &(*link)->next_included;
        }
    }

  /* At this point, we know that LINE is an unused line number, and
     *LINK points to the entry an #inclusion at that line should
     precede.  */
  new = new_source_file (source->table, included);
  new->included_by = source;
  new->included_at_line = line;
  new->next_included = *link;
  *link = new;

  return new;
}