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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  convert_modes (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_sync_lock_test_and_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_builtin_sync_mem (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
expand_builtin_lock_test_and_set (enum machine_mode mode, tree arglist,
				  rtx target)
{
  rtx val, mem;
  enum machine_mode old_mode;

  /* Expand the operands.  */
  mem = get_builtin_sync_mem (TREE_VALUE (arglist), mode);

  arglist = TREE_CHAIN (arglist);
  val = expand_expr (TREE_VALUE (arglist), NULL, mode, EXPAND_NORMAL);
  /* If VAL is promoted to a wider mode, convert it back to MODE.  Take care
     of CONST_INTs, where we know the old_mode only from the call argument.  */
  old_mode = GET_MODE (val);
  if (old_mode == VOIDmode)
    old_mode = TYPE_MODE (TREE_TYPE (TREE_VALUE (arglist)));
  val = convert_modes (mode, old_mode, val, 1);

  return expand_sync_lock_test_and_set (mem, val, target);
}