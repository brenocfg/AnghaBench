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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  ASHIFT 136 
#define  ASHIFTRT 135 
#define  CONST_INT 134 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  LSHIFTRT 133 
#define  MULT 132 
#define  REG 131 
#define  ROTATE 130 
#define  ROTATERT 129 
#define  SUBREG 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int int_log2 (int) ; 

__attribute__((used)) static const char *
shift_op (rtx op, HOST_WIDE_INT *amountp)
{
  const char * mnem;
  enum rtx_code code = GET_CODE (op);

  switch (GET_CODE (XEXP (op, 1)))
    {
    case REG:
    case SUBREG:
      *amountp = -1;
      break;

    case CONST_INT:
      *amountp = INTVAL (XEXP (op, 1));
      break;

    default:
      gcc_unreachable ();
    }

  switch (code)
    {
    case ASHIFT:
      mnem = "asl";
      break;

    case ASHIFTRT:
      mnem = "asr";
      break;

    case LSHIFTRT:
      mnem = "lsr";
      break;

    case ROTATE:
      gcc_assert (*amountp != -1);
      *amountp = 32 - *amountp;

      /* Fall through.  */

    case ROTATERT:
      mnem = "ror";
      break;

    case MULT:
      /* We never have to worry about the amount being other than a
	 power of 2, since this case can never be reloaded from a reg.  */
      gcc_assert (*amountp != -1);
      *amountp = int_log2 (*amountp);
      return "asl";

    default:
      gcc_unreachable ();
    }

  if (*amountp != -1)
    {
      /* This is not 100% correct, but follows from the desire to merge
	 multiplication by a power of 2 with the recognizer for a
	 shift.  >=32 is not a valid shift for "asl", so we must try and
	 output a shift that produces the correct arithmetical result.
	 Using lsr #32 is identical except for the fact that the carry bit
	 is not set correctly if we set the flags; but we never use the
	 carry bit from such an operation, so we can ignore that.  */
      if (code == ROTATERT)
	/* Rotate is just modulo 32.  */
	*amountp &= 31;
      else if (*amountp != (*amountp & 31))
	{
	  if (code == ASHIFT)
	    mnem = "lsr";
	  *amountp = 32;
	}

      /* Shifts of 0 are no-ops.  */
      if (*amountp == 0)
	return NULL;
    }

  return mnem;
}