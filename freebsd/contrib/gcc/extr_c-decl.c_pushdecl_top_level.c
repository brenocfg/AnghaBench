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
 scalar_t__ CONST_DECL ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_SYMBOL_BINDING (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ external_scope ; 
 scalar_t__ file_scope ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
pushdecl_top_level (tree x)
{
  tree name;
  bool nested = false;
  gcc_assert (TREE_CODE (x) == VAR_DECL || TREE_CODE (x) == CONST_DECL);

  name = DECL_NAME (x);

 gcc_assert (TREE_CODE (x) == CONST_DECL || !I_SYMBOL_BINDING (name));

  if (TREE_PUBLIC (x))
    {
      bind (name, x, external_scope, /*invisible=*/true, /*nested=*/false);
      nested = true;
    }
  if (file_scope)
    bind (name, x, file_scope, /*invisible=*/false, nested);

  return x;
}