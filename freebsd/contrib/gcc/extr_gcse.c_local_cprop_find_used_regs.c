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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_WORD ; 
 int GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
#define  POST_DEC 137 
#define  POST_INC 136 
#define  POST_MODIFY 135 
#define  PRE_DEC 134 
#define  PRE_INC 133 
#define  PRE_MODIFY 132 
#define  SIGN_EXTRACT 131 
#define  STRICT_LOW_PART 130 
#define  SUBREG 129 
 int /*<<< orphan*/  SUBREG_REG (scalar_t__) ; 
#define  ZERO_EXTRACT 128 
 int /*<<< orphan*/  find_used_regs (scalar_t__*,void*) ; 

__attribute__((used)) static void
local_cprop_find_used_regs (rtx *xptr, void *data)
{
  rtx x = *xptr;

  if (x == 0)
    return;

  switch (GET_CODE (x))
    {
    case ZERO_EXTRACT:
    case SIGN_EXTRACT:
    case STRICT_LOW_PART:
      return;

    case PRE_DEC:
    case PRE_INC:
    case POST_DEC:
    case POST_INC:
    case PRE_MODIFY:
    case POST_MODIFY:
      /* Can only legitimately appear this early in the context of
	 stack pushes for function arguments, but handle all of the
	 codes nonetheless.  */
      return;

    case SUBREG:
      /* Setting a subreg of a register larger than word_mode leaves
	 the non-written words unchanged.  */
      if (GET_MODE_BITSIZE (GET_MODE (SUBREG_REG (x))) > BITS_PER_WORD)
	return;
      break;

    default:
      break;
    }

  find_used_regs (xptr, data);
}