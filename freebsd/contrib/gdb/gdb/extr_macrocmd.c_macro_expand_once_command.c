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
 char* macro_expand_once (char*,int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  standard_macro_lookup ; 

__attribute__((used)) static void
macro_expand_once_command (char *exp, int from_tty)
{
  struct macro_scope *ms = NULL;
  char *expanded = NULL;
  struct cleanup *cleanup_chain = make_cleanup (free_current_contents, &ms);
  make_cleanup (free_current_contents, &expanded);

  /* You know, when the user doesn't specify any expression, it would be
     really cool if this defaulted to the last expression evaluated.
     And it should set the once-expanded text as the new `last
     expression'.  That way, you could just hit return over and over and
     see the expression expanded one level at a time.  */
  if (! exp || ! *exp)
    error ("You must follow the `macro expand-once' command with"
           " the expression\n"
           "you want to expand.");

  ms = default_macro_scope ();
  if (ms)
    {
      expanded = macro_expand_once (exp, standard_macro_lookup, ms);
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