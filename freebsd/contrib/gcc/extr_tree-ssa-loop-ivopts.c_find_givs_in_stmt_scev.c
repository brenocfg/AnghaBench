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
struct ivopts_data {struct loop* current_loop; } ;
struct TYPE_4__ {void* step; void* base; } ;
typedef  TYPE_1__ affine_iv ;

/* Variables and functions */
 scalar_t__ MODIFY_EXPR ; 
 void* NULL_TREE ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 scalar_t__ contains_abnormal_ssa_name_p (void*) ; 
 void* expand_simple_operations (void*) ; 
 int /*<<< orphan*/  simple_iv (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static bool
find_givs_in_stmt_scev (struct ivopts_data *data, tree stmt, affine_iv *iv)
{
  tree lhs;
  struct loop *loop = data->current_loop;

  iv->base = NULL_TREE;
  iv->step = NULL_TREE;

  if (TREE_CODE (stmt) != MODIFY_EXPR)
    return false;

  lhs = TREE_OPERAND (stmt, 0);
  if (TREE_CODE (lhs) != SSA_NAME)
    return false;

  if (!simple_iv (loop, stmt, TREE_OPERAND (stmt, 1), iv, true))
    return false;
  iv->base = expand_simple_operations (iv->base);

  if (contains_abnormal_ssa_name_p (iv->base)
      || contains_abnormal_ssa_name_p (iv->step))
    return false;

  return true;
}