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
 scalar_t__ PTRMEM_CST ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ build_ptrmemfunc_access_expr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_ptrmemfunc_cst (scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  pfn_identifier ; 

__attribute__((used)) static tree
pfn_from_ptrmemfunc (tree t)
{
  if (TREE_CODE (t) == PTRMEM_CST)
    {
      tree delta;
      tree pfn;

      expand_ptrmemfunc_cst (t, &delta, &pfn);
      if (pfn)
	return pfn;
    }

  return build_ptrmemfunc_access_expr (t, pfn_identifier);
}