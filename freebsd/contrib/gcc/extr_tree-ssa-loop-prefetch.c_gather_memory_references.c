#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct mem_ref_group {int dummy; } ;
struct loop {unsigned int num_nodes; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {struct loop* loop_father; } ;

/* Variables and functions */
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ REFERENCE_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (TYPE_1__*) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  gather_memory_references_ref (struct loop*,struct mem_ref_group**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__** get_loop_body_in_dom_order (struct loop*) ; 

__attribute__((used)) static struct mem_ref_group *
gather_memory_references (struct loop *loop)
{
  basic_block *body = get_loop_body_in_dom_order (loop);
  basic_block bb;
  unsigned i;
  block_stmt_iterator bsi;
  tree stmt, lhs, rhs;
  struct mem_ref_group *refs = NULL;

  /* Scan the loop body in order, so that the former references precede the
     later ones.  */
  for (i = 0; i < loop->num_nodes; i++)
    {
      bb = body[i];
      if (bb->loop_father != loop)
	continue;

      for (bsi = bsi_start (bb); !bsi_end_p (bsi); bsi_next (&bsi))
	{
	  stmt = bsi_stmt (bsi);
	  if (TREE_CODE (stmt) != MODIFY_EXPR)
	    continue;

	  lhs = TREE_OPERAND (stmt, 0);
	  rhs = TREE_OPERAND (stmt, 1);

	  if (REFERENCE_CLASS_P (rhs))
	    gather_memory_references_ref (loop, &refs, rhs, false, stmt);
	  if (REFERENCE_CLASS_P (lhs))
	    gather_memory_references_ref (loop, &refs, lhs, true, stmt);
	}
    }
  free (body);

  return refs;
}