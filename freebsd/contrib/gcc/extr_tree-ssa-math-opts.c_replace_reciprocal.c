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
typedef  int /*<<< orphan*/  use_operand_p ;
typedef  scalar_t__ tree ;
struct occurrence {scalar_t__ recip_def_stmt; scalar_t__ recip_def; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {scalar_t__ aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  MULT_EXPR ; 
 int /*<<< orphan*/  SET_USE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_SET_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USE_STMT (int /*<<< orphan*/ ) ; 
 TYPE_1__* bb_for_stmt (scalar_t__) ; 
 int /*<<< orphan*/  fold_stmt_inplace (scalar_t__) ; 
 int /*<<< orphan*/  update_stmt (scalar_t__) ; 

__attribute__((used)) static inline void
replace_reciprocal (use_operand_p use_p)
{
  tree use_stmt = USE_STMT (use_p);
  basic_block bb = bb_for_stmt (use_stmt);
  struct occurrence *occ = (struct occurrence *) bb->aux;

  if (occ->recip_def && use_stmt != occ->recip_def_stmt)
    {
      TREE_SET_CODE (TREE_OPERAND (use_stmt, 1), MULT_EXPR);
      SET_USE (use_p, occ->recip_def);
      fold_stmt_inplace (use_stmt);
      update_stmt (use_stmt);
    }
}