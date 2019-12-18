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

/* Variables and functions */
 size_t FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ REG ; 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_ARCH64 ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const_zero_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fp_high_losum_p (int /*<<< orphan*/ ) ; 
 int fp_mov_p (int /*<<< orphan*/ ) ; 
 int fp_sethi_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mem_min_alignment (int /*<<< orphan*/ ,int) ; 
 scalar_t__* reg_renumber ; 
 int register_ok_for_ldd (int /*<<< orphan*/ ) ; 
 scalar_t__ reload_in_progress ; 
 scalar_t__ strict_memory_address_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sparc_extra_constraint_check (rtx op, int c, int strict)
{
  int reload_ok_mem;

  if (TARGET_ARCH64
      && (c == 'T' || c == 'U'))
    return 0;

  switch (c)
    {
    case 'Q':
      return fp_sethi_p (op);

    case 'R':
      return fp_mov_p (op);

    case 'S':
      return fp_high_losum_p (op);

    case 'U':
      if (! strict
	  || (GET_CODE (op) == REG
	      && (REGNO (op) < FIRST_PSEUDO_REGISTER
		  || reg_renumber[REGNO (op)] >= 0)))
	return register_ok_for_ldd (op);

      return 0;

    case 'W':
    case 'T':
      break;

    case 'Y':
      return const_zero_operand (op, GET_MODE (op));

    default:
      return 0;
    }

  /* Our memory extra constraints have to emulate the
     behavior of 'm' and 'o' in order for reload to work
     correctly.  */
  if (GET_CODE (op) == MEM)
    {
      reload_ok_mem = 0;
      if ((TARGET_ARCH64 || mem_min_alignment (op, 8))
	  && (! strict
	      || strict_memory_address_p (Pmode, XEXP (op, 0))))
	reload_ok_mem = 1;
    }
  else
    {
      reload_ok_mem = (reload_in_progress
		       && GET_CODE (op) == REG
		       && REGNO (op) >= FIRST_PSEUDO_REGISTER
		       && reg_renumber [REGNO (op)] < 0);
    }

  return reload_ok_mem;
}