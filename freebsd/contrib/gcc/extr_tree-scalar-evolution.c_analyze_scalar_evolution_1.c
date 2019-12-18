#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct loop {int dummy; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {struct loop* loop_father; } ;

/* Variables and functions */
#define  MODIFY_EXPR 129 
 int /*<<< orphan*/  NULL_TREE ; 
#define  PHI_NODE 128 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int VECTOR_TYPE ; 
 int /*<<< orphan*/  automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 
 TYPE_1__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_not_analyzed_yet ; 
 int /*<<< orphan*/  compute_scalar_evolution_in_loop (struct loop*,struct loop*,int /*<<< orphan*/ ) ; 
 struct loop* find_common_loop (struct loop*,struct loop*) ; 
 int /*<<< orphan*/  flow_bb_inside_loop_p (struct loop*,TYPE_1__*) ; 
 int /*<<< orphan*/  fold_used_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interpret_condition_phi (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interpret_loop_phi (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interpret_rhs_modify_expr (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_phi_node_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointer_used_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_scalar_evolution (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
analyze_scalar_evolution_1 (struct loop *loop, tree var, tree res)
{
  tree def, type = TREE_TYPE (var);
  basic_block bb;
  struct loop *def_loop;

  if (loop == NULL || TREE_CODE (type) == VECTOR_TYPE)
    return chrec_dont_know;

  if (TREE_CODE (var) != SSA_NAME)
    return interpret_rhs_modify_expr (loop, NULL_TREE, var, type);

  def = SSA_NAME_DEF_STMT (var);
  bb = bb_for_stmt (def);
  def_loop = bb ? bb->loop_father : NULL;

  if (bb == NULL
      || !flow_bb_inside_loop_p (loop, bb))
    {
      /* Keep the symbolic form.  */
      res = var;
      goto set_and_end;
    }

  if (res != chrec_not_analyzed_yet)
    {
      if (loop != bb->loop_father)
	res = compute_scalar_evolution_in_loop 
	    (find_common_loop (loop, bb->loop_father), bb->loop_father, res);

      goto set_and_end;
    }

  if (loop != def_loop)
    {
      res = analyze_scalar_evolution_1 (def_loop, var, chrec_not_analyzed_yet);
      res = compute_scalar_evolution_in_loop (loop, def_loop, res);

      goto set_and_end;
    }

  switch (TREE_CODE (def))
    {
    case MODIFY_EXPR:
      res = interpret_rhs_modify_expr (loop, def, TREE_OPERAND (def, 1), type);

      if (POINTER_TYPE_P (type)
	  && !automatically_generated_chrec_p (res)
	  && pointer_used_p (var))
	res = fold_used_pointer (res, def);
      break;

    case PHI_NODE:
      if (loop_phi_node_p (def))
	res = interpret_loop_phi (loop, def);
      else
	res = interpret_condition_phi (loop, def);
      break;

    default:
      res = chrec_dont_know;
      break;
    }

 set_and_end:

  /* Keep the symbolic form.  */
  if (res == chrec_dont_know)
    res = var;

  if (loop == def_loop)
    set_scalar_evolution (var, res);

  return res;
}