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
 int /*<<< orphan*/  DECL_WEAK (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ SUPPORTS_WEAK ; 
 scalar_t__ TREE_ASM_WRITTEN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_weak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weak_decls ; 

void
declare_weak (tree decl)
{
  if (! TREE_PUBLIC (decl))
    error ("weak declaration of %q+D must be public", decl);
  else if (TREE_CODE (decl) == FUNCTION_DECL && TREE_ASM_WRITTEN (decl))
    error ("weak declaration of %q+D must precede definition", decl);
  else if (SUPPORTS_WEAK)
    {
      if (! DECL_WEAK (decl))
	weak_decls = tree_cons (NULL, decl, weak_decls);
    }
  else
    warning (0, "weak declaration of %q+D not supported", decl);

  mark_weak (decl);
}