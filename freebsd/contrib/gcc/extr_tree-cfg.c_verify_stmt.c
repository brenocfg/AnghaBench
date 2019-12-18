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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ OMP_DIRECTIVE_P (scalar_t__) ; 
 int /*<<< orphan*/  debug_generic_stmt (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  is_gimple_stmt (scalar_t__) ; 
 scalar_t__ lookup_stmt_eh_region (scalar_t__) ; 
 scalar_t__ tree_can_throw_internal (scalar_t__) ; 
 int /*<<< orphan*/  tree_could_throw_p (scalar_t__) ; 
 int /*<<< orphan*/  verify_expr ; 
 scalar_t__ walk_tree (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
verify_stmt (tree stmt, bool last_in_block)
{
  tree addr;

  if (OMP_DIRECTIVE_P (stmt))
    {
      /* OpenMP directives are validated by the FE and never operated
	 on by the optimizers.  Furthermore, OMP_FOR may contain
	 non-gimple expressions when the main index variable has had
	 its address taken.  This does not affect the loop itself
	 because the header of an OMP_FOR is merely used to determine
	 how to setup the parallel iteration.  */
      return false;
    }

  if (!is_gimple_stmt (stmt))
    {
      error ("is not a valid GIMPLE statement");
      goto fail;
    }

  addr = walk_tree (&stmt, verify_expr, NULL, NULL);
  if (addr)
    {
      debug_generic_stmt (addr);
      return true;
    }

  /* If the statement is marked as part of an EH region, then it is
     expected that the statement could throw.  Verify that when we
     have optimizations that simplify statements such that we prove
     that they cannot throw, that we update other data structures
     to match.  */
  if (lookup_stmt_eh_region (stmt) >= 0)
    {
      if (!tree_could_throw_p (stmt))
	{
	  error ("statement marked for throw, but doesn%'t");
	  goto fail;
	}
      if (!last_in_block && tree_can_throw_internal (stmt))
	{
	  error ("statement marked for throw in middle of block");
	  goto fail;
	}
    }

  return false;

 fail:
  debug_generic_stmt (stmt);
  return true;
}