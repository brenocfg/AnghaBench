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
 scalar_t__ TREE_BINFO ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PROTECTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accessible_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

bool
enforce_access (tree basetype_path, tree decl, tree diag_decl)
{
  gcc_assert (TREE_CODE (basetype_path) == TREE_BINFO);

  if (!accessible_p (basetype_path, decl, true))
    {
      if (TREE_PRIVATE (decl))
	error ("%q+#D is private", diag_decl);
      else if (TREE_PROTECTED (decl))
	error ("%q+#D is protected", diag_decl);
      else
	error ("%q+#D is inaccessible", diag_decl);
      error ("within this context");
      return false;
    }

  return true;
}