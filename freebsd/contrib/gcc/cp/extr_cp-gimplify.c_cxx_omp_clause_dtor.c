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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/ * CP_OMP_CLAUSE_INFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * cxx_omp_clause_apply_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

tree
cxx_omp_clause_dtor (tree clause, tree decl)
{
  tree info = CP_OMP_CLAUSE_INFO (clause);
  tree ret = NULL;

  if (info)
    ret = cxx_omp_clause_apply_fn (TREE_VEC_ELT (info, 1), decl, NULL);

  return ret;
}