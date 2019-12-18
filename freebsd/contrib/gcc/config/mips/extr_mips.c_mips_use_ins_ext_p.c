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
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ BITS_PER_WORD ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISA_HAS_EXT_INS ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  register_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
mips_use_ins_ext_p (rtx op, rtx size, rtx position)
{
  HOST_WIDE_INT len, pos;

  if (!ISA_HAS_EXT_INS
      || !register_operand (op, VOIDmode)
      || GET_MODE_BITSIZE (GET_MODE (op)) > BITS_PER_WORD)
    return false;

  len = INTVAL (size);
  pos = INTVAL (position);
  
  if (len <= 0 || len >= GET_MODE_BITSIZE (GET_MODE (op)) 
      || pos < 0 || pos + len > GET_MODE_BITSIZE (GET_MODE (op)))
    return false;

  return true;
}