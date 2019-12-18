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
typedef  enum omp_clause_code { ____Placeholder_omp_clause_code } omp_clause_code ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ OMP_CLAUSE_CHAIN (scalar_t__) ; 
 int OMP_CLAUSE_CODE (scalar_t__) ; 

__attribute__((used)) static tree
find_omp_clause (tree clauses, enum omp_clause_code kind)
{
  for (; clauses ; clauses = OMP_CLAUSE_CHAIN (clauses))
    if (OMP_CLAUSE_CODE (clauses) == kind)
      return clauses;

  return NULL_TREE;
}