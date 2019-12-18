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
struct s390_address {int pointer; int literal_pool; scalar_t__ disp; scalar_t__ indx; scalar_t__ base; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {scalar_t__ base_reg; scalar_t__ decomposed_literal_pool_addresses_ok_p; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ ARG_POINTER_REGNUM ; 
 scalar_t__ CONST ; 
 scalar_t__ CONSTANT_POOL_ADDRESS_P (scalar_t__) ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  DISP_IN_RANGE (scalar_t__) ; 
 scalar_t__ FRAME_POINTER_REGNUM ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ HARD_FRAME_POINTER_REGNUM ; 
 scalar_t__ INTVAL (scalar_t__) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ MINUS ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PIC_OFFSET_TABLE_REGNUM ; 
 scalar_t__ PLUS ; 
 scalar_t__ Pmode ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ REG_POINTER (scalar_t__) ; 
 scalar_t__ SImode ; 
 scalar_t__ STACK_POINTER_REGNUM ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ UNSPEC ; 
 int UNSPEC_GOT ; 
 int UNSPEC_GOTNTPOFF ; 
#define  UNSPEC_LTREF 129 
#define  UNSPEC_LTREL_BASE 128 
 int UNSPEC_LTREL_OFFSET ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int XINT (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ arg_pointer_rtx ; 
 TYPE_2__* cfun ; 
 int flag_pic ; 
 scalar_t__ frame_pointer_needed ; 
 scalar_t__ frame_pointer_rtx ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__) ; 
 scalar_t__ gen_rtx_CONST (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_REG (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_UNSPEC (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_pool_mode (scalar_t__) ; 
 scalar_t__ plus_constant (scalar_t__,scalar_t__) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 
 scalar_t__ return_address_pointer_rtx ; 
 scalar_t__ virtual_stack_vars_rtx ; 

__attribute__((used)) static int
s390_decompose_address (rtx addr, struct s390_address *out)
{
  HOST_WIDE_INT offset = 0;
  rtx base = NULL_RTX;
  rtx indx = NULL_RTX;
  rtx disp = NULL_RTX;
  rtx orig_disp;
  bool pointer = false;
  bool base_ptr = false;
  bool indx_ptr = false;
  bool literal_pool = false;

  /* We may need to substitute the literal pool base register into the address
     below.  However, at this point we do not know which register is going to
     be used as base, so we substitute the arg pointer register.  This is going
     to be treated as holding a pointer below -- it shouldn't be used for any
     other purpose.  */
  rtx fake_pool_base = gen_rtx_REG (Pmode, ARG_POINTER_REGNUM);

  /* Decompose address into base + index + displacement.  */

  if (GET_CODE (addr) == REG || GET_CODE (addr) == UNSPEC)
    base = addr;

  else if (GET_CODE (addr) == PLUS)
    {
      rtx op0 = XEXP (addr, 0);
      rtx op1 = XEXP (addr, 1);
      enum rtx_code code0 = GET_CODE (op0);
      enum rtx_code code1 = GET_CODE (op1);

      if (code0 == REG || code0 == UNSPEC)
	{
	  if (code1 == REG || code1 == UNSPEC)
	    {
	      indx = op0;	/* index + base */
	      base = op1;
	    }

	  else
	    {
	      base = op0;	/* base + displacement */
	      disp = op1;
	    }
	}

      else if (code0 == PLUS)
	{
	  indx = XEXP (op0, 0);	/* index + base + disp */
	  base = XEXP (op0, 1);
	  disp = op1;
	}

      else
	{
	  return false;
	}
    }

  else
    disp = addr;		/* displacement */

  /* Extract integer part of displacement.  */
  orig_disp = disp;
  if (disp)
    {
      if (GET_CODE (disp) == CONST_INT)
	{
	  offset = INTVAL (disp);
	  disp = NULL_RTX;
	}
      else if (GET_CODE (disp) == CONST
	       && GET_CODE (XEXP (disp, 0)) == PLUS
	       && GET_CODE (XEXP (XEXP (disp, 0), 1)) == CONST_INT)
	{
	  offset = INTVAL (XEXP (XEXP (disp, 0), 1));
	  disp = XEXP (XEXP (disp, 0), 0);
	}
    }

  /* Strip off CONST here to avoid special case tests later.  */
  if (disp && GET_CODE (disp) == CONST)
    disp = XEXP (disp, 0);

  /* We can convert literal pool addresses to
     displacements by basing them off the base register.  */
  if (disp && GET_CODE (disp) == SYMBOL_REF && CONSTANT_POOL_ADDRESS_P (disp))
    {
      /* Either base or index must be free to hold the base register.  */
      if (!base)
        base = fake_pool_base, literal_pool = true;
      else if (!indx)
        indx = fake_pool_base, literal_pool = true;
      else
        return false;

      /* Mark up the displacement.  */
      disp = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, disp),
			     UNSPEC_LTREL_OFFSET);
    }

  /* Validate base register.  */
  if (base)
    {
      if (GET_CODE (base) == UNSPEC)
	switch (XINT (base, 1))
	  {
	  case UNSPEC_LTREF:
	    if (!disp)
	      disp = gen_rtx_UNSPEC (Pmode, 
				     gen_rtvec (1, XVECEXP (base, 0, 0)),
				     UNSPEC_LTREL_OFFSET);
	    else
	      return false;

	    base = XVECEXP (base, 0, 1);
	    break;

	  case UNSPEC_LTREL_BASE:
	    if (XVECLEN (base, 0) == 1)
	      base = fake_pool_base, literal_pool = true;
	    else
	      base = XVECEXP (base, 0, 1);
	    break;

	  default:
	    return false;
	  }

      if (!REG_P (base) 
	  || (GET_MODE (base) != SImode 
	      && GET_MODE (base) != Pmode))
	return false;

      if (REGNO (base) == STACK_POINTER_REGNUM
	  || REGNO (base) == FRAME_POINTER_REGNUM
	  || ((reload_completed || reload_in_progress)
	      && frame_pointer_needed
	      && REGNO (base) == HARD_FRAME_POINTER_REGNUM)
	  || REGNO (base) == ARG_POINTER_REGNUM
          || (flag_pic
              && REGNO (base) == PIC_OFFSET_TABLE_REGNUM))
        pointer = base_ptr = true;

      if ((reload_completed || reload_in_progress)
	  && base == cfun->machine->base_reg)
        pointer = base_ptr = literal_pool = true;
    }

  /* Validate index register.  */
  if (indx)
    {
      if (GET_CODE (indx) == UNSPEC)
	switch (XINT (indx, 1))
	  {
	  case UNSPEC_LTREF:
	    if (!disp)
	      disp = gen_rtx_UNSPEC (Pmode, 
				     gen_rtvec (1, XVECEXP (indx, 0, 0)),
				     UNSPEC_LTREL_OFFSET);
	    else
	      return false;

	    indx = XVECEXP (indx, 0, 1);
	    break;

	  case UNSPEC_LTREL_BASE:
	    if (XVECLEN (indx, 0) == 1)
	      indx = fake_pool_base, literal_pool = true;
	    else
	      indx = XVECEXP (indx, 0, 1);
	    break;

	  default:
	    return false;
	  }

      if (!REG_P (indx) 
	  || (GET_MODE (indx) != SImode
	      && GET_MODE (indx) != Pmode))
	return false;

      if (REGNO (indx) == STACK_POINTER_REGNUM
	  || REGNO (indx) == FRAME_POINTER_REGNUM
	  || ((reload_completed || reload_in_progress)
	      && frame_pointer_needed
	      && REGNO (indx) == HARD_FRAME_POINTER_REGNUM)
	  || REGNO (indx) == ARG_POINTER_REGNUM
          || (flag_pic
              && REGNO (indx) == PIC_OFFSET_TABLE_REGNUM))
        pointer = indx_ptr = true;

      if ((reload_completed || reload_in_progress)
	  && indx == cfun->machine->base_reg)
        pointer = indx_ptr = literal_pool = true;
    }

  /* Prefer to use pointer as base, not index.  */
  if (base && indx && !base_ptr
      && (indx_ptr || (!REG_POINTER (base) && REG_POINTER (indx))))
    {
      rtx tmp = base;
      base = indx;
      indx = tmp;
    }

  /* Validate displacement.  */
  if (!disp)
    {
      /* If virtual registers are involved, the displacement will change later 
	 anyway as the virtual registers get eliminated.  This could make a 
	 valid displacement invalid, but it is more likely to make an invalid 
	 displacement valid, because we sometimes access the register save area 
	 via negative offsets to one of those registers.
	 Thus we don't check the displacement for validity here.  If after
	 elimination the displacement turns out to be invalid after all,
	 this is fixed up by reload in any case.  */
      if (base != arg_pointer_rtx 
	  && indx != arg_pointer_rtx 
	  && base != return_address_pointer_rtx 
	  && indx != return_address_pointer_rtx
	  && base != frame_pointer_rtx 
	  && indx != frame_pointer_rtx
	  && base != virtual_stack_vars_rtx 
	  && indx != virtual_stack_vars_rtx)
	if (!DISP_IN_RANGE (offset))
	  return false;
    }
  else
    {
      /* All the special cases are pointers.  */
      pointer = true;

      /* In the small-PIC case, the linker converts @GOT
         and @GOTNTPOFF offsets to possible displacements.  */
      if (GET_CODE (disp) == UNSPEC
          && (XINT (disp, 1) == UNSPEC_GOT
	      || XINT (disp, 1) == UNSPEC_GOTNTPOFF)
	  && flag_pic == 1)
        {
	  ;
        }

      /* Accept chunkified literal pool symbol references.  */
      else if (cfun && cfun->machine
	       && cfun->machine->decomposed_literal_pool_addresses_ok_p
	       && GET_CODE (disp) == MINUS
               && GET_CODE (XEXP (disp, 0)) == LABEL_REF
               && GET_CODE (XEXP (disp, 1)) == LABEL_REF)
        {
	  ;
        }

      /* Accept literal pool references.  */
      else if (GET_CODE (disp) == UNSPEC
	       && XINT (disp, 1) == UNSPEC_LTREL_OFFSET)
        {
	  orig_disp = gen_rtx_CONST (Pmode, disp);
	  if (offset)
	    {
	      /* If we have an offset, make sure it does not
		 exceed the size of the constant pool entry.  */
	      rtx sym = XVECEXP (disp, 0, 0);
	      if (offset >= GET_MODE_SIZE (get_pool_mode (sym)))
		return false;

              orig_disp = plus_constant (orig_disp, offset);
	    }
        }

      else
	return false;
    }

  if (!base && !indx)
    pointer = true;

  if (out)
    {
      out->base = base;
      out->indx = indx;
      out->disp = orig_disp;
      out->pointer = pointer;
      out->literal_pool = literal_pool;
    }

  return true;
}