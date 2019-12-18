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
struct ui_file {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ build_address_symbolic (int /*<<< orphan*/ ,int,char**,int*,char**,int*,int*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ print_symbol_filename ; 

void
print_address_symbolic (CORE_ADDR addr, struct ui_file *stream, int do_demangle,
			char *leadin)
{
  char *name = NULL;
  char *filename = NULL;
  int unmapped = 0;
  int offset = 0;
  int line = 0;

  /* throw away both name and filename */
  struct cleanup *cleanup_chain = make_cleanup (free_current_contents, &name);
  make_cleanup (free_current_contents, &filename);

  if (build_address_symbolic (addr, do_demangle, &name, &offset, &filename, &line, &unmapped))
    {
      do_cleanups (cleanup_chain);
      return;
    }

  fputs_filtered (leadin, stream);
  if (unmapped)
    fputs_filtered ("<*", stream);
  else
    fputs_filtered ("<", stream);
  fputs_filtered (name, stream);
  if (offset != 0)
    fprintf_filtered (stream, "+%u", (unsigned int) offset);

  /* Append source filename and line number if desired.  Give specific
     line # of this addr, if we have it; else line # of the nearest symbol.  */
  if (print_symbol_filename && filename != NULL)
    {
      if (line != -1)
	fprintf_filtered (stream, " at %s:%d", filename, line);
      else
	fprintf_filtered (stream, " in %s", filename);
    }
  if (unmapped)
    fputs_filtered ("*>", stream);
  else
    fputs_filtered (">", stream);

  do_cleanups (cleanup_chain);
}