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
 int OMP_CLAUSE_DEFAULT_SHARED ; 
 int OMP_CLAUSE_DEFAULT_UNSPECIFIED ; 
 scalar_t__ TREE_READONLY (int /*<<< orphan*/ ) ; 

enum omp_clause_default_kind
c_omp_predetermined_sharing (tree decl)
{
  /* Variables with const-qualified type having no mutable member
     are predetermined shared.  */
  if (TREE_READONLY (decl))
    return OMP_CLAUSE_DEFAULT_SHARED;

  return OMP_CLAUSE_DEFAULT_UNSPECIFIED;
}