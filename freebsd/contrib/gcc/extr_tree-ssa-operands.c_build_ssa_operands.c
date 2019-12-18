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
struct TYPE_3__ {int has_volatile_ops; int /*<<< orphan*/ * addresses_taken; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_v_may_defs ; 
 int /*<<< orphan*/  build_v_must_defs ; 
 int /*<<< orphan*/  build_vuses ; 
 int /*<<< orphan*/  finalize_ssa_stmt_operands (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_stmt_ann (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  operand_build_sort_virtual (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_ssa_operands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_ssa_stmt_operands () ; 

__attribute__((used)) static void
build_ssa_operands (tree stmt)
{
  stmt_ann_t ann = get_stmt_ann (stmt);
  
  /* Initially assume that the statement has no volatile operands and
     does not take the address of any symbols.  */
  if (ann)
    {
      ann->has_volatile_ops = false;
      if (ann->addresses_taken)
	ann->addresses_taken = NULL;
    }

  start_ssa_stmt_operands ();

  parse_ssa_operands (stmt);
  operand_build_sort_virtual (build_vuses);
  operand_build_sort_virtual (build_v_may_defs);
  operand_build_sort_virtual (build_v_must_defs);

  finalize_ssa_stmt_operands (stmt);
}