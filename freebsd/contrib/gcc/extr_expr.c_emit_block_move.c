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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum block_op_methods { ____Placeholder_block_op_methods } block_op_methods ;

/* Variables and functions */
 int /*<<< orphan*/  BLKmode ; 
#define  BLOCK_OP_CALL_PARM 131 
#define  BLOCK_OP_NORMAL 130 
#define  BLOCK_OP_NO_LIBCALL 129 
#define  BLOCK_OP_TAILCALL 128 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 unsigned int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MOVE_BY_PIECES_P (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  NO_DEFER_POP ; 
 int /*<<< orphan*/  OK_DEFER_POP ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int block_move_libcall_safe_for_call_parm () ; 
 int /*<<< orphan*/  emit_block_move_via_libcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_block_move_via_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ emit_block_move_via_movmem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  move_by_pieces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shallow_copy_rtx (int /*<<< orphan*/ ) ; 

rtx
emit_block_move (rtx x, rtx y, rtx size, enum block_op_methods method)
{
  bool may_use_call;
  rtx retval = 0;
  unsigned int align;

  switch (method)
    {
    case BLOCK_OP_NORMAL:
    case BLOCK_OP_TAILCALL:
      may_use_call = true;
      break;

    case BLOCK_OP_CALL_PARM:
      may_use_call = block_move_libcall_safe_for_call_parm ();

      /* Make inhibit_defer_pop nonzero around the library call
	 to force it to pop the arguments right away.  */
      NO_DEFER_POP;
      break;

    case BLOCK_OP_NO_LIBCALL:
      may_use_call = false;
      break;

    default:
      gcc_unreachable ();
    }

  align = MIN (MEM_ALIGN (x), MEM_ALIGN (y));

  gcc_assert (MEM_P (x));
  gcc_assert (MEM_P (y));
  gcc_assert (size);

  /* Make sure we've got BLKmode addresses; store_one_arg can decide that
     block copy is more efficient for other large modes, e.g. DCmode.  */
  x = adjust_address (x, BLKmode, 0);
  y = adjust_address (y, BLKmode, 0);

  /* Set MEM_SIZE as appropriate for this block copy.  The main place this
     can be incorrect is coming from __builtin_memcpy.  */
  if (GET_CODE (size) == CONST_INT)
    {
      if (INTVAL (size) == 0)
	return 0;

      x = shallow_copy_rtx (x);
      y = shallow_copy_rtx (y);
      set_mem_size (x, size);
      set_mem_size (y, size);
    }

  if (GET_CODE (size) == CONST_INT && MOVE_BY_PIECES_P (INTVAL (size), align))
    move_by_pieces (x, y, INTVAL (size), align, 0);
  else if (emit_block_move_via_movmem (x, y, size, align))
    ;
  else if (may_use_call)
    retval = emit_block_move_via_libcall (x, y, size,
					  method == BLOCK_OP_TAILCALL);
  else
    emit_block_move_via_loop (x, y, size, align);

  if (method == BLOCK_OP_CALL_PARM)
    OK_DEFER_POP;

  return retval;
}