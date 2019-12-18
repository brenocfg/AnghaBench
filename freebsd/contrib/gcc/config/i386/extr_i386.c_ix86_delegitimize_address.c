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
 scalar_t__ ASHIFT ; 
 scalar_t__ CONST ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ MEM ; 
 scalar_t__ MULT ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PIC_OFFSET_TABLE_REGNUM ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_MACHO ; 
 scalar_t__ UNSPEC ; 
 scalar_t__ UNSPEC_GOT ; 
 scalar_t__ UNSPEC_GOTOFF ; 
 scalar_t__ UNSPEC_GOTPCREL ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XINT (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ darwin_local_data_pic (scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static rtx
ix86_delegitimize_address (rtx orig_x)
{
  rtx x = orig_x;
  /* reg_addend is NULL or a multiple of some register.  */
  rtx reg_addend = NULL_RTX;
  /* const_addend is NULL or a const_int.  */
  rtx const_addend = NULL_RTX;
  /* This is the result, or NULL.  */
  rtx result = NULL_RTX;

  if (GET_CODE (x) == MEM)
    x = XEXP (x, 0);

  if (TARGET_64BIT)
    {
      if (GET_CODE (x) != CONST
	  || GET_CODE (XEXP (x, 0)) != UNSPEC
	  || XINT (XEXP (x, 0), 1) != UNSPEC_GOTPCREL
	  || GET_CODE (orig_x) != MEM)
	return orig_x;
      return XVECEXP (XEXP (x, 0), 0, 0);
    }

  if (GET_CODE (x) != PLUS
      || GET_CODE (XEXP (x, 1)) != CONST)
    return orig_x;

  if (GET_CODE (XEXP (x, 0)) == REG
      && REGNO (XEXP (x, 0)) == PIC_OFFSET_TABLE_REGNUM)
    /* %ebx + GOT/GOTOFF */
    ;
  else if (GET_CODE (XEXP (x, 0)) == PLUS)
    {
      /* %ebx + %reg * scale + GOT/GOTOFF */
      reg_addend = XEXP (x, 0);
      if (GET_CODE (XEXP (reg_addend, 0)) == REG
	  && REGNO (XEXP (reg_addend, 0)) == PIC_OFFSET_TABLE_REGNUM)
	reg_addend = XEXP (reg_addend, 1);
      else if (GET_CODE (XEXP (reg_addend, 1)) == REG
	       && REGNO (XEXP (reg_addend, 1)) == PIC_OFFSET_TABLE_REGNUM)
	reg_addend = XEXP (reg_addend, 0);
      else
	return orig_x;
      if (GET_CODE (reg_addend) != REG
	  && GET_CODE (reg_addend) != MULT
	  && GET_CODE (reg_addend) != ASHIFT)
	return orig_x;
    }
  else
    return orig_x;

  x = XEXP (XEXP (x, 1), 0);
  if (GET_CODE (x) == PLUS
      && GET_CODE (XEXP (x, 1)) == CONST_INT)
    {
      const_addend = XEXP (x, 1);
      x = XEXP (x, 0);
    }

  if (GET_CODE (x) == UNSPEC
      && ((XINT (x, 1) == UNSPEC_GOT && GET_CODE (orig_x) == MEM)
	  || (XINT (x, 1) == UNSPEC_GOTOFF && GET_CODE (orig_x) != MEM)))
    result = XVECEXP (x, 0, 0);

  if (TARGET_MACHO && darwin_local_data_pic (x)
      && GET_CODE (orig_x) != MEM)
    result = XEXP (x, 0);

  if (! result)
    return orig_x;

  if (const_addend)
    result = gen_rtx_PLUS (Pmode, result, const_addend);
  if (reg_addend)
    result = gen_rtx_PLUS (Pmode, reg_addend, result);
  return result;
}