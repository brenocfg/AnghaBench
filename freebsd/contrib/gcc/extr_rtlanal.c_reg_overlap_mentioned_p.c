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
#define  CC0 137 
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int /*<<< orphan*/  GET_RTX_LENGTH (int) ; 
#define  MEM 136 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
#define  PARALLEL 135 
#define  PC 134 
#define  REG 133 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
#define  SCRATCH 132 
#define  SIGN_EXTRACT 131 
#define  STRICT_LOW_PART 130 
#define  SUBREG 129 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  XVECLEN (int /*<<< orphan*/ ,int) ; 
#define  ZERO_EXTRACT 128 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int** hard_regno_nregs ; 
 int refers_to_regno_p (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int subreg_regno (int /*<<< orphan*/ ) ; 

int
reg_overlap_mentioned_p (rtx x, rtx in)
{
  unsigned int regno, endregno;

  /* If either argument is a constant, then modifying X can not
     affect IN.  Here we look at IN, we can profitably combine
     CONSTANT_P (x) with the switch statement below.  */
  if (CONSTANT_P (in))
    return 0;

 recurse:
  switch (GET_CODE (x))
    {
    case STRICT_LOW_PART:
    case ZERO_EXTRACT:
    case SIGN_EXTRACT:
      /* Overly conservative.  */
      x = XEXP (x, 0);
      goto recurse;

    case SUBREG:
      regno = REGNO (SUBREG_REG (x));
      if (regno < FIRST_PSEUDO_REGISTER)
	regno = subreg_regno (x);
      goto do_reg;

    case REG:
      regno = REGNO (x);
    do_reg:
      endregno = regno + (regno < FIRST_PSEUDO_REGISTER
			  ? hard_regno_nregs[regno][GET_MODE (x)] : 1);
      return refers_to_regno_p (regno, endregno, in, (rtx*) 0);

    case MEM:
      {
	const char *fmt;
	int i;

	if (MEM_P (in))
	  return 1;

	fmt = GET_RTX_FORMAT (GET_CODE (in));
	for (i = GET_RTX_LENGTH (GET_CODE (in)) - 1; i >= 0; i--)
	  if (fmt[i] == 'e')
	    {
	      if (reg_overlap_mentioned_p (x, XEXP (in, i)))
		return 1;
	    }
	  else if (fmt[i] == 'E')
	    {
	      int j;
	      for (j = XVECLEN (in, i) - 1; j >= 0; --j)
		if (reg_overlap_mentioned_p (x, XVECEXP (in, i, j)))
		  return 1;
	    }

	return 0;
      }

    case SCRATCH:
    case PC:
    case CC0:
      return reg_mentioned_p (x, in);

    case PARALLEL:
      {
	int i;

	/* If any register in here refers to it we return true.  */
	for (i = XVECLEN (x, 0) - 1; i >= 0; i--)
	  if (XEXP (XVECEXP (x, 0, i), 0) != 0
	      && reg_overlap_mentioned_p (XEXP (XVECEXP (x, 0, i), 0), in))
	    return 1;
	return 0;
      }

    default:
      gcc_assert (CONSTANT_P (x));
      return 0;
    }
}