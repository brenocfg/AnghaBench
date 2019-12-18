#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {scalar_t__ (* use_aeabi_atexit ) () ;} ;
struct TYPE_4__ {TYPE_1__ cxx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  BCS_FN_BODY ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_HAS_TRIVIAL_DESTRUCTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_unary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_mark_addressable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dk_no_check ; 
 int /*<<< orphan*/  end_cleanup_fn () ; 
 int /*<<< orphan*/  finish_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_expr_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_use_cxa_atexit ; 
 int /*<<< orphan*/  get_atexit_node () ; 
 int /*<<< orphan*/  get_dso_handle_node () ; 
 int /*<<< orphan*/  mark_used (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_pointer_node ; 
 int /*<<< orphan*/  pop_deferring_access_checks () ; 
 int /*<<< orphan*/  push_deferring_access_checks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_cleanup_fn () ; 
 scalar_t__ stub1 () ; 
 TYPE_2__ targetm ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_zero_node ; 

tree
register_dtor_fn (tree decl)
{
  tree cleanup;
  tree compound_stmt;
  tree args;
  tree fcall;

  if (TYPE_HAS_TRIVIAL_DESTRUCTOR (TREE_TYPE (decl)))
    return void_zero_node;

  /* Call build_cleanup before we enter the anonymous function so that
     any access checks will be done relative to the current scope,
     rather than the scope of the anonymous function.  */
  build_cleanup (decl);

  /* Now start the function.  */
  cleanup = start_cleanup_fn ();

  /* Now, recompute the cleanup.  It may contain SAVE_EXPRs that refer
     to the original function, rather than the anonymous one.  That
     will make the back-end think that nested functions are in use,
     which causes confusion.  */

  push_deferring_access_checks (dk_no_check);
  fcall = build_cleanup (decl);
  pop_deferring_access_checks ();

  /* Create the body of the anonymous function.  */
  compound_stmt = begin_compound_stmt (BCS_FN_BODY);
  finish_expr_stmt (fcall);
  finish_compound_stmt (compound_stmt);
  end_cleanup_fn ();

  /* Call atexit with the cleanup function.  */
  cxx_mark_addressable (cleanup);
  mark_used (cleanup);
  cleanup = build_unary_op (ADDR_EXPR, cleanup, 0);
  if (flag_use_cxa_atexit)
    {
      args = tree_cons (NULL_TREE,
			build_unary_op (ADDR_EXPR, get_dso_handle_node (), 0),
			NULL_TREE);
      if (targetm.cxx.use_aeabi_atexit ())
	{
	  args = tree_cons (NULL_TREE, cleanup, args);
	  args = tree_cons (NULL_TREE, null_pointer_node, args);
	}
      else
	{
	  args = tree_cons (NULL_TREE, null_pointer_node, args);
	  args = tree_cons (NULL_TREE, cleanup, args);
	}
    }
  else
    args = tree_cons (NULL_TREE, cleanup, NULL_TREE);
  return build_function_call (get_atexit_node (), args);
}