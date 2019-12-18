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
struct tree_omp_clause {int dummy; } ;
typedef  enum omp_clause_code { ____Placeholder_omp_clause_code } omp_clause_code ;

/* Variables and functions */
 int /*<<< orphan*/  OMP_CLAUSE ; 
 int /*<<< orphan*/  OMP_CLAUSE_SET_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_SET_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ggc_alloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ omp_clause_kind ; 
 int* omp_clause_num_ops ; 
 int /*<<< orphan*/ * tree_node_counts ; 
 int* tree_node_sizes ; 

tree
build_omp_clause (enum omp_clause_code code)
{
  tree t;
  int size, length;

  length = omp_clause_num_ops[code];
  size = (sizeof (struct tree_omp_clause) + (length - 1) * sizeof (tree));

  t = ggc_alloc (size);
  memset (t, 0, size);
  TREE_SET_CODE (t, OMP_CLAUSE);
  OMP_CLAUSE_SET_CODE (t, code);

#ifdef GATHER_STATISTICS
  tree_node_counts[(int) omp_clause_kind]++;
  tree_node_sizes[(int) omp_clause_kind] += size;
#endif
  
  return t;
}