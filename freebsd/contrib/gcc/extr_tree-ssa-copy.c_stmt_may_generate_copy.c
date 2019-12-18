#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* stmt_ann_t ;
struct TYPE_3__ {scalar_t__ has_volatile_ops; } ;

/* Variables and functions */
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ PHI_NODE ; 
 int /*<<< orphan*/  PHI_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_OCCURS_IN_ABNORMAL_PHI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_OP_ALL_VIRTUALS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZERO_SSA_OPERANDS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ do_store_copy_prop ; 
 TYPE_1__* stmt_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
stmt_may_generate_copy (tree stmt)
{
  tree lhs, rhs;
  stmt_ann_t ann;

  if (TREE_CODE (stmt) == PHI_NODE)
    return !SSA_NAME_OCCURS_IN_ABNORMAL_PHI (PHI_RESULT (stmt));

  if (TREE_CODE (stmt) != MODIFY_EXPR)
    return false;

  lhs = TREE_OPERAND (stmt, 0);
  rhs = TREE_OPERAND (stmt, 1);
  ann = stmt_ann (stmt);

  /* If the statement has volatile operands, it won't generate a
     useful copy.  */
  if (ann->has_volatile_ops)
    return false;

  /* If we are not doing store copy-prop, statements with loads and/or
     stores will never generate a useful copy.  */
  if (!do_store_copy_prop
      && !ZERO_SSA_OPERANDS (stmt, SSA_OP_ALL_VIRTUALS))
    return false;

  /* Otherwise, the only statements that generate useful copies are
     assignments whose RHS is just an SSA name that doesn't flow
     through abnormal edges.  */
  return (do_store_copy_prop
	  && TREE_CODE (lhs) == SSA_NAME)
	 || (TREE_CODE (rhs) == SSA_NAME
	     && !SSA_NAME_OCCURS_IN_ABNORMAL_PHI (rhs));
}