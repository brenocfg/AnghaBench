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
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
#define  ARRAY_REF 136 
#define  COMPLEX_CST 135 
#define  COMPLEX_EXPR 134 
#define  COMPONENT_REF 133 
 int /*<<< orphan*/  IMAGPART_EXPR ; 
#define  INDIRECT_REF 132 
#define  PARM_DECL 131 
 int /*<<< orphan*/  REALPART_EXPR ; 
#define  RESULT_DECL 130 
#define  SSA_NAME 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_IMAGPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_REALPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_component_ssa_name (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gimplify_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
extract_component (block_stmt_iterator *bsi, tree t, bool imagpart_p,
		   bool gimple_p)
{
  switch (TREE_CODE (t))
    {
    case COMPLEX_CST:
      return imagpart_p ? TREE_IMAGPART (t) : TREE_REALPART (t);

    case COMPLEX_EXPR:
      return TREE_OPERAND (t, imagpart_p);

    case VAR_DECL:
    case RESULT_DECL:
    case PARM_DECL:
    case INDIRECT_REF:
    case COMPONENT_REF:
    case ARRAY_REF:
      {
	tree inner_type = TREE_TYPE (TREE_TYPE (t));

	t = build1 ((imagpart_p ? IMAGPART_EXPR : REALPART_EXPR),
		    inner_type, unshare_expr (t));

	if (gimple_p)
	  t = gimplify_val (bsi, inner_type, t);

	return t;
      }

    case SSA_NAME:
      return get_component_ssa_name (t, imagpart_p);

    default:
      gcc_unreachable ();
    }
}