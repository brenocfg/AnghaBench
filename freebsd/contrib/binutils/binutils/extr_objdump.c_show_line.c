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
struct print_file_list {char const* filename; unsigned int last_line; scalar_t__ first; struct print_file_list* next; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 unsigned int SHOW_PRECEDING_CONTEXT_LINES ; 
 int /*<<< orphan*/  bfd_find_nearest_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**,char const**,unsigned int*) ; 
 int /*<<< orphan*/  dump_lines (struct print_file_list*,unsigned int,unsigned int) ; 
 scalar_t__ file_start_context ; 
 int /*<<< orphan*/  free (char const*) ; 
 char const* prev_functionname ; 
 unsigned int prev_line ; 
 struct print_file_list* print_files ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  syms ; 
 struct print_file_list* update_source_path (char const*) ; 
 scalar_t__ with_line_numbers ; 
 scalar_t__ with_source_code ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
show_line (bfd *abfd, asection *section, bfd_vma addr_offset)
{
  const char *filename;
  const char *functionname;
  unsigned int line;

  if (! with_line_numbers && ! with_source_code)
    return;

  if (! bfd_find_nearest_line (abfd, section, syms, addr_offset, &filename,
			       &functionname, &line))
    return;

  if (filename != NULL && *filename == '\0')
    filename = NULL;
  if (functionname != NULL && *functionname == '\0')
    functionname = NULL;

  if (with_line_numbers)
    {
      if (functionname != NULL
	  && (prev_functionname == NULL
	      || strcmp (functionname, prev_functionname) != 0))
	printf ("%s():\n", functionname);
      if (line > 0 && line != prev_line)
	printf ("%s:%u\n", filename == NULL ? "???" : filename, line);
    }

  if (with_source_code
      && filename != NULL
      && line > 0)
    {
      struct print_file_list **pp, *p;
      unsigned l;

      for (pp = &print_files; *pp != NULL; pp = &(*pp)->next)
	if (strcmp ((*pp)->filename, filename) == 0)
	  break;
      p = *pp;

      if (p == NULL)
	  p = update_source_path (filename);

      if (p != NULL && line != p->last_line)
	{
	  if (file_start_context && p->first) 
	    l = 1;
	  else 
	    {
	      l = line - SHOW_PRECEDING_CONTEXT_LINES;
	      if (l >= line) 
		l = 1;
	      if (p->last_line >= l && p->last_line <= line)
		l = p->last_line + 1;
	    }
	  dump_lines (p, l, line);
	  p->last_line = line;
	  p->first = 0;
	}
    }

  if (functionname != NULL
      && (prev_functionname == NULL
	  || strcmp (functionname, prev_functionname) != 0))
    {
      if (prev_functionname != NULL)
	free (prev_functionname);
      prev_functionname = xmalloc (strlen (functionname) + 1);
      strcpy (prev_functionname, functionname);
    }

  if (line > 0 && line != prev_line)
    prev_line = line;
}