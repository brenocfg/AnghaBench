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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum block_op_methods { ____Placeholder_block_op_methods } block_op_methods ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int BLKmode ; 
 int BLOCK_OP_NORMAL ; 
 int BLOCK_OP_TAILCALL ; 
 scalar_t__ CLEAR_BY_PIECES_P (scalar_t__,unsigned int) ; 
 scalar_t__ COMPLEX_MODE_P (int) ; 
 int /*<<< orphan*/ * CONST0_RTX (int) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 int GET_MODE (int /*<<< orphan*/ *) ; 
 int GET_MODE_INNER (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ *) ; 
 unsigned int MEM_ALIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_by_pieces (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/ * clear_storage_via_libcall (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * const0_rtx ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ set_storage_via_setmem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  write_complex_part (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

rtx
clear_storage (rtx object, rtx size, enum block_op_methods method)
{
  enum machine_mode mode = GET_MODE (object);
  unsigned int align;

  gcc_assert (method == BLOCK_OP_NORMAL || method == BLOCK_OP_TAILCALL);

  /* If OBJECT is not BLKmode and SIZE is the same size as its mode,
     just move a zero.  Otherwise, do this a piece at a time.  */
  if (mode != BLKmode
      && GET_CODE (size) == CONST_INT
      && INTVAL (size) == (HOST_WIDE_INT) GET_MODE_SIZE (mode))
    {
      rtx zero = CONST0_RTX (mode);
      if (zero != NULL)
	{
	  emit_move_insn (object, zero);
	  return NULL;
	}

      if (COMPLEX_MODE_P (mode))
	{
	  zero = CONST0_RTX (GET_MODE_INNER (mode));
	  if (zero != NULL)
	    {
	      write_complex_part (object, zero, 0);
	      write_complex_part (object, zero, 1);
	      return NULL;
	    }
	}
    }

  if (size == const0_rtx)
    return NULL;

  align = MEM_ALIGN (object);

  if (GET_CODE (size) == CONST_INT
      && CLEAR_BY_PIECES_P (INTVAL (size), align))
    clear_by_pieces (object, INTVAL (size), align);
  else if (set_storage_via_setmem (object, size, const0_rtx, align))
    ;
  else
    return clear_storage_via_libcall (object, size,
				      method == BLOCK_OP_TAILCALL);

  return NULL;
}