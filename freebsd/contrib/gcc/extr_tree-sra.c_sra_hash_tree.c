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
typedef  int hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_FIELD_BIT_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FIELD_OFFSET (int /*<<< orphan*/ ) ; 
 int DECL_UID (int /*<<< orphan*/ ) ; 
#define  FIELD_DECL 133 
#define  INTEGER_CST 132 
#define  PARM_DECL 131 
#define  RANGE_EXPR 130 
#define  RESULT_DECL 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int iterative_hash_expr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static hashval_t
sra_hash_tree (tree t)
{
  hashval_t h;

  switch (TREE_CODE (t))
    {
    case VAR_DECL:
    case PARM_DECL:
    case RESULT_DECL:
      h = DECL_UID (t);
      break;

    case INTEGER_CST:
      h = TREE_INT_CST_LOW (t) ^ TREE_INT_CST_HIGH (t);
      break;

    case RANGE_EXPR:
      h = iterative_hash_expr (TREE_OPERAND (t, 0), 0);
      h = iterative_hash_expr (TREE_OPERAND (t, 1), h);
      break;

    case FIELD_DECL:
      /* We can have types that are compatible, but have different member
	 lists, so we can't hash fields by ID.  Use offsets instead.  */
      h = iterative_hash_expr (DECL_FIELD_OFFSET (t), 0);
      h = iterative_hash_expr (DECL_FIELD_BIT_OFFSET (t), h);
      break;

    default:
      gcc_unreachable ();
    }

  return h;
}