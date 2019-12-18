#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  location_t ;
struct TYPE_2__ {unsigned int rid; scalar_t__* decl; int /*<<< orphan*/  pretty; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_EMPTY_STMT (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  UNKNOWN_LOCATION ; 
 int /*<<< orphan*/  current_function_decl ; 
 TYPE_1__* fname_vars ; 
 scalar_t__ input_line ; 
 int /*<<< orphan*/  input_location ; 
 scalar_t__ make_fname_decl (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pedwarn (char*,scalar_t__) ; 
 scalar_t__ pop_stmt_list (scalar_t__) ; 
 scalar_t__ push_stmt_list () ; 
 int /*<<< orphan*/  saved_function_name_decls ; 
 scalar_t__ stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_cons (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

tree
fname_decl (unsigned int rid, tree id)
{
  unsigned ix;
  tree decl = NULL_TREE;

  for (ix = 0; fname_vars[ix].decl; ix++)
    if (fname_vars[ix].rid == rid)
      break;

  decl = *fname_vars[ix].decl;
  if (!decl)
    {
      /* If a tree is built here, it would normally have the lineno of
	 the current statement.  Later this tree will be moved to the
	 beginning of the function and this line number will be wrong.
	 To avoid this problem set the lineno to 0 here; that prevents
	 it from appearing in the RTL.  */
      tree stmts;
      location_t saved_location = input_location;
#ifdef USE_MAPPED_LOCATION
      input_location = UNKNOWN_LOCATION;
#else
      input_line = 0;
#endif

      stmts = push_stmt_list ();
      decl = (*make_fname_decl) (id, fname_vars[ix].pretty);
      stmts = pop_stmt_list (stmts);
      if (!IS_EMPTY_STMT (stmts))
	saved_function_name_decls
	  = tree_cons (decl, stmts, saved_function_name_decls);
      *fname_vars[ix].decl = decl;
      input_location = saved_location;
    }
  if (!ix && !current_function_decl)
    pedwarn ("%qD is not defined outside of function scope", decl);

  return decl;
}