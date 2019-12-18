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
struct macro_source_file {int dummy; } ;
struct macro_scope {int line; struct macro_source_file* file; } ;
struct macro_definition {scalar_t__ kind; int argc; char** argv; char* replacement; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 struct macro_scope* default_macro_scope () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct macro_source_file* macro_definition_location (struct macro_source_file*,int,char*,int*) ; 
 scalar_t__ macro_function_like ; 
 struct macro_definition* macro_lookup_definition (struct macro_source_file*,int,char*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct macro_scope**) ; 
 int /*<<< orphan*/  show_pp_source_pos (int /*<<< orphan*/ ,struct macro_source_file*,int) ; 

__attribute__((used)) static void
info_macro_command (char *name, int from_tty)
{
  struct macro_scope *ms = NULL;
  struct cleanup *cleanup_chain = make_cleanup (free_current_contents, &ms);
  struct macro_definition *d;
  
  if (! name || ! *name)
    error ("You must follow the `info macro' command with the name"
           " of the macro\n"
           "whose definition you want to see.");

  ms = default_macro_scope ();
  if (! ms)
    error ("GDB has no preprocessor macro information for that code.");

  d = macro_lookup_definition (ms->file, ms->line, name);
  if (d)
    {
      int line;
      struct macro_source_file *file
        = macro_definition_location (ms->file, ms->line, name, &line);

      fprintf_filtered (gdb_stdout, "Defined at ");
      show_pp_source_pos (gdb_stdout, file, line);
      fprintf_filtered (gdb_stdout, "#define %s", name);
      if (d->kind == macro_function_like)
        {
          int i;

          fputs_filtered ("(", gdb_stdout);
          for (i = 0; i < d->argc; i++)
            {
              fputs_filtered (d->argv[i], gdb_stdout);
              if (i + 1 < d->argc)
                fputs_filtered (", ", gdb_stdout);
            }
          fputs_filtered (")", gdb_stdout);
        }
      fprintf_filtered (gdb_stdout, " %s\n", d->replacement);
    }
  else
    {
      fprintf_filtered (gdb_stdout,
                        "The symbol `%s' has no definition as a C/C++"
                        " preprocessor macro\n"
                        "at ", name);
      show_pp_source_pos (gdb_stdout, ms->file, ms->line);
    }

  do_cleanups (cleanup_chain);
}