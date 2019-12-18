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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_VECTOR ; 
#define  DFmode 129 
 int DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ *) ; 
 int GET_MODE_SIZE (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 scalar_t__ MEM ; 
 scalar_t__ MEM_READONLY_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMX_REGNO_P (scalar_t__) ; 
 int /*<<< orphan*/  PUT_MODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REAL_VALUE_TO_TARGET_DOUBLE (int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  REAL_VALUE_TO_TARGET_LONG_DOUBLE (int /*<<< orphan*/ ,long*) ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ *) ; 
 int SImode ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 int TFmode ; 
 int TImode ; 
 int /*<<< orphan*/  VOIDmode ; 
#define  XFmode 128 
 int /*<<< orphan*/ * adjust_address (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * copy_rtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * gen_int_mode (long,int) ; 
 int /*<<< orphan*/ * gen_rtx_REG (int,scalar_t__) ; 
 int /*<<< orphan*/ * immed_double_const (long,long,int) ; 
 int int_mode_for_mode (int) ; 
 int /*<<< orphan*/ * maybe_get_pool_constant (int /*<<< orphan*/ *) ; 
 scalar_t__ offsettable_memref_p (int /*<<< orphan*/ *) ; 
 int push_operand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_to_target (long*,int /*<<< orphan*/ *,int) ; 
 int reload_completed ; 
 int /*<<< orphan*/ * simplify_subreg (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_di (int /*<<< orphan*/ **,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  split_ti (int /*<<< orphan*/ **,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
ix86_split_to_parts (rtx operand, rtx *parts, enum machine_mode mode)
{
  int size;

  if (!TARGET_64BIT)
    size = mode==XFmode ? 3 : GET_MODE_SIZE (mode) / 4;
  else
    size = (GET_MODE_SIZE (mode) + 4) / 8;

  gcc_assert (GET_CODE (operand) != REG || !MMX_REGNO_P (REGNO (operand)));
  gcc_assert (size >= 2 && size <= 3);

  /* Optimize constant pool reference to immediates.  This is used by fp
     moves, that force all constants to memory to allow combining.  */
  if (GET_CODE (operand) == MEM && MEM_READONLY_P (operand))
    {
      rtx tmp = maybe_get_pool_constant (operand);
      if (tmp)
	operand = tmp;
    }

  if (GET_CODE (operand) == MEM && !offsettable_memref_p (operand))
    {
      /* The only non-offsetable memories we handle are pushes.  */
      int ok = push_operand (operand, VOIDmode);

      gcc_assert (ok);

      operand = copy_rtx (operand);
      PUT_MODE (operand, Pmode);
      parts[0] = parts[1] = parts[2] = operand;
      return size;
    }

  if (GET_CODE (operand) == CONST_VECTOR)
    {
      enum machine_mode imode = int_mode_for_mode (mode);
      /* Caution: if we looked through a constant pool memory above,
	 the operand may actually have a different mode now.  That's
	 ok, since we want to pun this all the way back to an integer.  */
      operand = simplify_subreg (imode, operand, GET_MODE (operand), 0);
      gcc_assert (operand != NULL);
      mode = imode;
    }

  if (!TARGET_64BIT)
    {
      if (mode == DImode)
	split_di (&operand, 1, &parts[0], &parts[1]);
      else
	{
	  if (REG_P (operand))
	    {
	      gcc_assert (reload_completed);
	      parts[0] = gen_rtx_REG (SImode, REGNO (operand) + 0);
	      parts[1] = gen_rtx_REG (SImode, REGNO (operand) + 1);
	      if (size == 3)
		parts[2] = gen_rtx_REG (SImode, REGNO (operand) + 2);
	    }
	  else if (offsettable_memref_p (operand))
	    {
	      operand = adjust_address (operand, SImode, 0);
	      parts[0] = operand;
	      parts[1] = adjust_address (operand, SImode, 4);
	      if (size == 3)
		parts[2] = adjust_address (operand, SImode, 8);
	    }
	  else if (GET_CODE (operand) == CONST_DOUBLE)
	    {
	      REAL_VALUE_TYPE r;
	      long l[4];

	      REAL_VALUE_FROM_CONST_DOUBLE (r, operand);
	      switch (mode)
		{
		case XFmode:
		  REAL_VALUE_TO_TARGET_LONG_DOUBLE (r, l);
		  parts[2] = gen_int_mode (l[2], SImode);
		  break;
		case DFmode:
		  REAL_VALUE_TO_TARGET_DOUBLE (r, l);
		  break;
		default:
		  gcc_unreachable ();
		}
	      parts[1] = gen_int_mode (l[1], SImode);
	      parts[0] = gen_int_mode (l[0], SImode);
	    }
	  else
	    gcc_unreachable ();
	}
    }
  else
    {
      if (mode == TImode)
	split_ti (&operand, 1, &parts[0], &parts[1]);
      if (mode == XFmode || mode == TFmode)
	{
	  enum machine_mode upper_mode = mode==XFmode ? SImode : DImode;
	  if (REG_P (operand))
	    {
	      gcc_assert (reload_completed);
	      parts[0] = gen_rtx_REG (DImode, REGNO (operand) + 0);
	      parts[1] = gen_rtx_REG (upper_mode, REGNO (operand) + 1);
	    }
	  else if (offsettable_memref_p (operand))
	    {
	      operand = adjust_address (operand, DImode, 0);
	      parts[0] = operand;
	      parts[1] = adjust_address (operand, upper_mode, 8);
	    }
	  else if (GET_CODE (operand) == CONST_DOUBLE)
	    {
	      REAL_VALUE_TYPE r;
	      long l[4];

	      REAL_VALUE_FROM_CONST_DOUBLE (r, operand);
	      real_to_target (l, &r, mode);

	      /* Do not use shift by 32 to avoid warning on 32bit systems.  */
	      if (HOST_BITS_PER_WIDE_INT >= 64)
	        parts[0]
		  = gen_int_mode
		      ((l[0] & (((HOST_WIDE_INT) 2 << 31) - 1))
		       + ((((HOST_WIDE_INT) l[1]) << 31) << 1),
		       DImode);
	      else
	        parts[0] = immed_double_const (l[0], l[1], DImode);

	      if (upper_mode == SImode)
	        parts[1] = gen_int_mode (l[2], SImode);
	      else if (HOST_BITS_PER_WIDE_INT >= 64)
	        parts[1]
		  = gen_int_mode
		      ((l[2] & (((HOST_WIDE_INT) 2 << 31) - 1))
		       + ((((HOST_WIDE_INT) l[3]) << 31) << 1),
		       DImode);
	      else
	        parts[1] = immed_double_const (l[2], l[3], DImode);
	    }
	  else
	    gcc_unreachable ();
	}
    }

  return size;
}