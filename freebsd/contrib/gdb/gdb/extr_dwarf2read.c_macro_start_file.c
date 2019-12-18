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
struct objfile {int /*<<< orphan*/  macro_cache; int /*<<< orphan*/  objfile_obstack; } ;
struct macro_source_file {int dummy; } ;
struct line_header {int dummy; } ;

/* Variables and functions */
 char* file_full_name (int,struct line_header*,char const*) ; 
 struct macro_source_file* macro_include (struct macro_source_file*,int,char*) ; 
 struct macro_source_file* macro_set_main (scalar_t__,char*) ; 
 scalar_t__ new_macro_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pending_macros ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static struct macro_source_file *
macro_start_file (int file, int line,
                  struct macro_source_file *current_file,
                  const char *comp_dir,
                  struct line_header *lh, struct objfile *objfile)
{
  /* The full name of this source file.  */
  char *full_name = file_full_name (file, lh, comp_dir);

  /* We don't create a macro table for this compilation unit
     at all until we actually get a filename.  */
  if (! pending_macros)
    pending_macros = new_macro_table (&objfile->objfile_obstack,
                                      objfile->macro_cache);

  if (! current_file)
    /* If we have no current file, then this must be the start_file
       directive for the compilation unit's main source file.  */
    current_file = macro_set_main (pending_macros, full_name);
  else
    current_file = macro_include (current_file, line, full_name);

  xfree (full_name);
              
  return current_file;
}