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
typedef  enum omp_clause_default_kind { ____Placeholder_omp_clause_default_kind } omp_clause_default_kind ;

/* Variables and functions */
 int /*<<< orphan*/  CP_DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_AGGR_TYPE (int /*<<< orphan*/ ) ; 
 int OMP_CLAUSE_DEFAULT_SHARED ; 
 int OMP_CLAUSE_DEFAULT_UNSPECIFIED ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 int c_omp_predetermined_sharing (int /*<<< orphan*/ ) ; 

enum omp_clause_default_kind
cxx_omp_predetermined_sharing (tree decl)
{
  enum omp_clause_default_kind kind;

  kind = c_omp_predetermined_sharing (decl);
  if (kind != OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    return kind;

  /* Static data members are predetermined as shared.  */
  if (TREE_STATIC (decl))
    {
      tree ctx = CP_DECL_CONTEXT (decl);
      if (TYPE_P (ctx) && IS_AGGR_TYPE (ctx))
	return OMP_CLAUSE_DEFAULT_SHARED;
    }

  return OMP_CLAUSE_DEFAULT_UNSPECIFIED;
}