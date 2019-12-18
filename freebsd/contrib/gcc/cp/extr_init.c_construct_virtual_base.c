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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ARGUMENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOKUP_COMPLAIN ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_if_stmt () ; 
 int /*<<< orphan*/  convert_to_base_statically (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_class_ref ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  expand_aggr_init_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_cleanup_for_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_if_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_if_stmt_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_then_clause (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
construct_virtual_base (tree vbase, tree arguments)
{
  tree inner_if_stmt;
  tree exp;
  tree flag;

  /* If there are virtual base classes with destructors, we need to
     emit cleanups to destroy them if an exception is thrown during
     the construction process.  These exception regions (i.e., the
     period during which the cleanups must occur) begin from the time
     the construction is complete to the end of the function.  If we
     create a conditional block in which to initialize the
     base-classes, then the cleanup region for the virtual base begins
     inside a block, and ends outside of that block.  This situation
     confuses the sjlj exception-handling code.  Therefore, we do not
     create a single conditional block, but one for each
     initialization.  (That way the cleanup regions always begin
     in the outer block.)  We trust the back-end to figure out
     that the FLAG will not change across initializations, and
     avoid doing multiple tests.  */
  flag = TREE_CHAIN (DECL_ARGUMENTS (current_function_decl));
  inner_if_stmt = begin_if_stmt ();
  finish_if_stmt_cond (flag, inner_if_stmt);

  /* Compute the location of the virtual base.  If we're
     constructing virtual bases, then we must be the most derived
     class.  Therefore, we don't have to look up the virtual base;
     we already know where it is.  */
  exp = convert_to_base_statically (current_class_ref, vbase);

  expand_aggr_init_1 (vbase, current_class_ref, exp, arguments,
		      LOOKUP_COMPLAIN);
  finish_then_clause (inner_if_stmt);
  finish_if_stmt (inner_if_stmt);

  expand_cleanup_for_base (vbase, flag);
}