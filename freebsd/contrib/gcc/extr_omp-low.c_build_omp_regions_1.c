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
struct omp_region {scalar_t__ type; void* cont; struct omp_region* outer; void* exit; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  void* basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int OMP_CONTINUE ; 
 scalar_t__ OMP_DIRECTIVE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ OMP_PARALLEL ; 
 int OMP_RETURN ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (void*) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  determine_parallel_type (struct omp_region*) ; 
 void* first_dom_son (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gcc_assert (struct omp_region*) ; 
 struct omp_region* new_omp_region (void*,int,struct omp_region*) ; 
 void* next_dom_son (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
build_omp_regions_1 (basic_block bb, struct omp_region *parent)
{
  block_stmt_iterator si;
  tree stmt;
  basic_block son;

  si = bsi_last (bb);
  if (!bsi_end_p (si) && OMP_DIRECTIVE_P (bsi_stmt (si)))
    {
      struct omp_region *region;
      enum tree_code code;

      stmt = bsi_stmt (si);
      code = TREE_CODE (stmt);

      if (code == OMP_RETURN)
	{
	  /* STMT is the return point out of region PARENT.  Mark it
	     as the exit point and make PARENT the immediately
	     enclosing region.  */
	  gcc_assert (parent);
	  region = parent;
	  region->exit = bb;
	  parent = parent->outer;

	  /* If REGION is a parallel region, determine whether it is
	     a combined parallel+workshare region.  */
	  if (region->type == OMP_PARALLEL)
	    determine_parallel_type (region);
	}
      else if (code == OMP_CONTINUE)
	{
	  gcc_assert (parent);
	  parent->cont = bb;
	}
      else
	{
	  /* Otherwise, this directive becomes the parent for a new
	     region.  */
	  region = new_omp_region (bb, code, parent);
	  parent = region;
	}
    }

  for (son = first_dom_son (CDI_DOMINATORS, bb);
       son;
       son = next_dom_son (CDI_DOMINATORS, son))
    build_omp_regions_1 (son, parent);
}