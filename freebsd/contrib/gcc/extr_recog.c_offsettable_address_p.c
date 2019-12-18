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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 unsigned int BIGGEST_ALIGNMENT ; 
 unsigned int BITS_PER_UNIT ; 
 int BLKmode ; 
 scalar_t__ CONSTANT_ADDRESS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 unsigned int GET_MODE_ALIGNMENT (int) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 scalar_t__ GET_RTX_CLASS (int) ; 
 scalar_t__ LO_SUM ; 
 int PLUS ; 
 int QImode ; 
 scalar_t__ RTX_AUTOINC ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * find_constant_term_loc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_rtx_LO_SUM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memory_address_p (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mode_dependent_address_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,unsigned int) ; 
 int strict_memory_address_p (int,int /*<<< orphan*/ ) ; 
 int stub1 (int,int /*<<< orphan*/ ) ; 
 int stub2 (int,int /*<<< orphan*/ ) ; 

int
offsettable_address_p (int strictp, enum machine_mode mode, rtx y)
{
  enum rtx_code ycode = GET_CODE (y);
  rtx z;
  rtx y1 = y;
  rtx *y2;
  int (*addressp) (enum machine_mode, rtx) =
    (strictp ? strict_memory_address_p : memory_address_p);
  unsigned int mode_sz = GET_MODE_SIZE (mode);

  if (CONSTANT_ADDRESS_P (y))
    return 1;

  /* Adjusting an offsettable address involves changing to a narrower mode.
     Make sure that's OK.  */

  if (mode_dependent_address_p (y))
    return 0;

  /* ??? How much offset does an offsettable BLKmode reference need?
     Clearly that depends on the situation in which it's being used.
     However, the current situation in which we test 0xffffffff is
     less than ideal.  Caveat user.  */
  if (mode_sz == 0)
    mode_sz = BIGGEST_ALIGNMENT / BITS_PER_UNIT;

  /* If the expression contains a constant term,
     see if it remains valid when max possible offset is added.  */

  if ((ycode == PLUS) && (y2 = find_constant_term_loc (&y1)))
    {
      int good;

      y1 = *y2;
      *y2 = plus_constant (*y2, mode_sz - 1);
      /* Use QImode because an odd displacement may be automatically invalid
	 for any wider mode.  But it should be valid for a single byte.  */
      good = (*addressp) (QImode, y);

      /* In any case, restore old contents of memory.  */
      *y2 = y1;
      return good;
    }

  if (GET_RTX_CLASS (ycode) == RTX_AUTOINC)
    return 0;

  /* The offset added here is chosen as the maximum offset that
     any instruction could need to add when operating on something
     of the specified mode.  We assume that if Y and Y+c are
     valid addresses then so is Y+d for all 0<d<c.  adjust_address will
     go inside a LO_SUM here, so we do so as well.  */
  if (GET_CODE (y) == LO_SUM
      && mode != BLKmode
      && mode_sz <= GET_MODE_ALIGNMENT (mode) / BITS_PER_UNIT)
    z = gen_rtx_LO_SUM (GET_MODE (y), XEXP (y, 0),
			plus_constant (XEXP (y, 1), mode_sz - 1));
  else
    z = plus_constant (y, mode_sz - 1);

  /* Use QImode because an odd displacement may be automatically invalid
     for any wider mode.  But it should be valid for a single byte.  */
  return (*addressp) (QImode, z);
}