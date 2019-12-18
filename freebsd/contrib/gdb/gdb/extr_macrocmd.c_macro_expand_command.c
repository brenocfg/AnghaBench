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
typedef  char macro_scope ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 char* default_macro_scope () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_stdout ; 
 char* macro_expand (char*,int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  standard_macro_lookup ; 

__attribute__((used)) static void
macro_expand_command (char *exp, int from_tty)
{
  struct macro_scope *ms = NULL;
  char *expanded = NULL;
  struct cleanup *cleanup_chain = make_cleanup (free_current_contents, &ms);
  make_cleanup (free_current_contents, &expanded);

  /* You know, when the user doesn't specify any expression, it would be
     really cool if this defaulted to the last expression evaluated.
     Then it would be easy to ask, "Hey, what did I just evaluate?"  But
     at the moment, the `print' commands don't save the last expression
     evaluated, just its value.  */
  if (! exp || ! *exp)
    error ("You must follow the `macro expand' command with the"
           " expression you\n"
           "want to expand.");

  ms = default_macro_scope ();
  if (ms)
    {
      expanded = macro_expand (exp, standard_macro_lookup, ms);
      fputs_filtered ("expands to: ", gdb_stdout);
      fputs_filtered (expanded, gdb_stdout);
      fputs_filtered ("\n", gdb_stdout);
    }
  else
    fputs_filtered ("GDB has no preprocessor macro information for "
                    "that code.\n",
                    gdb_stdout);

  do_cleanups (cleanup_chain);
  return;
}