#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct expr_hash_elt {scalar_t__ stmt; scalar_t__ rhs; scalar_t__ hash; } ;
struct TYPE_2__ {scalar_t__ (* types_compatible_p ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OEP_PURE_SAME ; 
 int /*<<< orphan*/  SSA_OP_VUSE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int compare_ssa_operands_equal (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__ lang_hooks ; 
 scalar_t__ operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
avail_expr_eq (const void *p1, const void *p2)
{
  tree stmt1 = ((struct expr_hash_elt *)p1)->stmt;
  tree rhs1 = ((struct expr_hash_elt *)p1)->rhs;
  tree stmt2 = ((struct expr_hash_elt *)p2)->stmt;
  tree rhs2 = ((struct expr_hash_elt *)p2)->rhs;

  /* If they are the same physical expression, return true.  */
  if (rhs1 == rhs2 && stmt1 == stmt2)
    return true;

  /* If their codes are not equal, then quit now.  */
  if (TREE_CODE (rhs1) != TREE_CODE (rhs2))
    return false;

  /* In case of a collision, both RHS have to be identical and have the
     same VUSE operands.  */
  if ((TREE_TYPE (rhs1) == TREE_TYPE (rhs2)
       || lang_hooks.types_compatible_p (TREE_TYPE (rhs1), TREE_TYPE (rhs2)))
      && operand_equal_p (rhs1, rhs2, OEP_PURE_SAME))
    {
      bool ret = compare_ssa_operands_equal (stmt1, stmt2, SSA_OP_VUSE);
      gcc_assert (!ret || ((struct expr_hash_elt *)p1)->hash
		  == ((struct expr_hash_elt *)p2)->hash);
      return ret;
    }

  return false;
}