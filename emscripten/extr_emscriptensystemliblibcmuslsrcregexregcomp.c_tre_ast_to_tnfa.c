#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* right; TYPE_4__* left; } ;
typedef  TYPE_1__ tre_union_t ;
typedef  int /*<<< orphan*/  tre_tnfa_transition_t ;
struct TYPE_7__ {int max; int min; TYPE_4__* arg; } ;
typedef  TYPE_2__ tre_iteration_t ;
struct TYPE_8__ {TYPE_4__* right; TYPE_4__* left; } ;
typedef  TYPE_3__ tre_catenation_t ;
struct TYPE_9__ {int type; int /*<<< orphan*/  firstpos; int /*<<< orphan*/  lastpos; scalar_t__ obj; } ;
typedef  TYPE_4__ tre_ast_node_t ;
typedef  int /*<<< orphan*/  reg_errcode_t ;

/* Variables and functions */
#define  CATENATION 131 
#define  ITERATION 130 
#define  LITERAL 129 
 int /*<<< orphan*/  REG_OK ; 
#define  UNION 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tre_make_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static reg_errcode_t
tre_ast_to_tnfa(tre_ast_node_t *node, tre_tnfa_transition_t *transitions,
		int *counts, int *offs)
{
  tre_union_t *uni;
  tre_catenation_t *cat;
  tre_iteration_t *iter;
  reg_errcode_t errcode = REG_OK;

  /* XXX - recurse using a stack!. */
  switch (node->type)
    {
    case LITERAL:
      break;
    case UNION:
      uni = (tre_union_t *)node->obj;
      errcode = tre_ast_to_tnfa(uni->left, transitions, counts, offs);
      if (errcode != REG_OK)
	return errcode;
      errcode = tre_ast_to_tnfa(uni->right, transitions, counts, offs);
      break;

    case CATENATION:
      cat = (tre_catenation_t *)node->obj;
      /* Add a transition from each position in cat->left->lastpos
	 to each position in cat->right->firstpos. */
      errcode = tre_make_trans(cat->left->lastpos, cat->right->firstpos,
			       transitions, counts, offs);
      if (errcode != REG_OK)
	return errcode;
      errcode = tre_ast_to_tnfa(cat->left, transitions, counts, offs);
      if (errcode != REG_OK)
	return errcode;
      errcode = tre_ast_to_tnfa(cat->right, transitions, counts, offs);
      break;

    case ITERATION:
      iter = (tre_iteration_t *)node->obj;
      assert(iter->max == -1 || iter->max == 1);

      if (iter->max == -1)
	{
	  assert(iter->min == 0 || iter->min == 1);
	  /* Add a transition from each last position in the iterated
	     expression to each first position. */
	  errcode = tre_make_trans(iter->arg->lastpos, iter->arg->firstpos,
				   transitions, counts, offs);
	  if (errcode != REG_OK)
	    return errcode;
	}
      errcode = tre_ast_to_tnfa(iter->arg, transitions, counts, offs);
      break;
    }
  return errcode;
}