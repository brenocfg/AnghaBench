#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {scalar_t__ (* arg_partial_bytes ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;
typedef  int /*<<< orphan*/  CUMULATIVE_ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  FUNCTION_ARG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FUNCTION_ARG_ADVANCE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INIT_CUMULATIVE_ARGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ PUSH_ARGS ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_PARM_STACK_SPACE (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ emit_block_move_libcall_fn (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ targetm ; 
 scalar_t__ void_list_node ; 

__attribute__((used)) static bool
block_move_libcall_safe_for_call_parm (void)
{
  /* If arguments are pushed on the stack, then they're safe.  */
  if (PUSH_ARGS)
    return true;

  /* If registers go on the stack anyway, any argument is sure to clobber
     an outgoing argument.  */
#if defined (REG_PARM_STACK_SPACE) && defined (OUTGOING_REG_PARM_STACK_SPACE)
  {
    tree fn = emit_block_move_libcall_fn (false);
    (void) fn;
    if (REG_PARM_STACK_SPACE (fn) != 0)
      return false;
  }
#endif

  /* If any argument goes in memory, then it might clobber an outgoing
     argument.  */
  {
    CUMULATIVE_ARGS args_so_far;
    tree fn, arg;

    fn = emit_block_move_libcall_fn (false);
    INIT_CUMULATIVE_ARGS (args_so_far, TREE_TYPE (fn), NULL_RTX, 0, 3);

    arg = TYPE_ARG_TYPES (TREE_TYPE (fn));
    for ( ; arg != void_list_node ; arg = TREE_CHAIN (arg))
      {
	enum machine_mode mode = TYPE_MODE (TREE_VALUE (arg));
	rtx tmp = FUNCTION_ARG (args_so_far, mode, NULL_TREE, 1);
	if (!tmp || !REG_P (tmp))
	  return false;
	if (targetm.calls.arg_partial_bytes (&args_so_far, mode, NULL, 1))
	  return false;
	FUNCTION_ARG_ADVANCE (args_so_far, mode, NULL_TREE, 1);
      }
  }
  return true;
}