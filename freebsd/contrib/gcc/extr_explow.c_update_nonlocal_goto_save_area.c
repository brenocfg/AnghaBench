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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/  nonlocal_goto_save_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_REF ; 
 int /*<<< orphan*/  EXPAND_WRITE ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  SAVE_NONLOCAL ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  build4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  emit_stack_save (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  ptr_type_node ; 

void
update_nonlocal_goto_save_area (void)
{
  tree t_save;
  rtx r_save;

  /* The nonlocal_goto_save_area object is an array of N pointers.  The
     first one is used for the frame pointer save; the rest are sized by
     STACK_SAVEAREA_MODE.  Create a reference to array index 1, the first
     of the stack save area slots.  */
  t_save = build4 (ARRAY_REF, ptr_type_node, cfun->nonlocal_goto_save_area,
		   integer_one_node, NULL_TREE, NULL_TREE);
  r_save = expand_expr (t_save, NULL_RTX, VOIDmode, EXPAND_WRITE);

  emit_stack_save (SAVE_NONLOCAL, &r_save, NULL_RTX);
}