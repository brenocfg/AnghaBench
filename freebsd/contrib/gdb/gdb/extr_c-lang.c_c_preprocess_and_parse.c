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
struct macro_scope {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int c_parse () ; 
 struct macro_scope* default_macro_scope () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 scalar_t__ expression_context_block ; 
 int /*<<< orphan*/  expression_context_pc ; 
 void* expression_macro_lookup_baton ; 
 int /*<<< orphan*/  expression_macro_lookup_func ; 
 int /*<<< orphan*/  find_pc_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  macro_original_text ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct macro_scope**) ; 
 int /*<<< orphan*/  null_macro_lookup ; 
 struct macro_scope* sal_macro_scope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_macro_cleanup ; 
 int /*<<< orphan*/  standard_macro_lookup ; 

__attribute__((used)) static int
c_preprocess_and_parse (void)
{
  /* Set up a lookup function for the macro expander.  */
  struct macro_scope *scope = 0;
  struct cleanup *back_to = make_cleanup (free_current_contents, &scope);

  if (expression_context_block)
    scope = sal_macro_scope (find_pc_line (expression_context_pc, 0));
  else
    scope = default_macro_scope ();

  if (scope)
    {
      expression_macro_lookup_func = standard_macro_lookup;
      expression_macro_lookup_baton = (void *) scope;
    }
  else
    {
      expression_macro_lookup_func = null_macro_lookup;
      expression_macro_lookup_baton = 0;      
    }

  gdb_assert (! macro_original_text);
  make_cleanup (scan_macro_cleanup, 0);

  {
    int result = c_parse ();
    do_cleanups (back_to);
    return result;
  }
}