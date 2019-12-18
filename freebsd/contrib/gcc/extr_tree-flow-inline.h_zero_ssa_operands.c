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
typedef  int /*<<< orphan*/  ssa_op_iter ;

/* Variables and functions */
 int op_iter_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_iter_init_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool
zero_ssa_operands (tree stmt, int flags)
{
  ssa_op_iter iter;

  op_iter_init_tree (&iter, stmt, flags);
  return op_iter_done (&iter);
}