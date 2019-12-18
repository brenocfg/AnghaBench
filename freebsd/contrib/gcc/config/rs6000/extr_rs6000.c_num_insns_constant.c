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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  CONST_DOUBLE 129 
 int CONST_DOUBLE_HIGH (int /*<<< orphan*/ ) ; 
 int CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
#define  CONST_INT 128 
 int DImode ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_TO_TARGET_DOUBLE (int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  REAL_VALUE_TO_TARGET_SINGLE (int /*<<< orphan*/ ,long) ; 
 int SFmode ; 
 int /*<<< orphan*/  TARGET_32BIT ; 
 int VOIDmode ; 
 int /*<<< orphan*/  WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  mask64_operand (int /*<<< orphan*/ ,int) ; 
 int num_insns_constant_wide (int) ; 

int
num_insns_constant (rtx op, enum machine_mode mode)
{
  HOST_WIDE_INT low, high;

  switch (GET_CODE (op))
    {
    case CONST_INT:
#if HOST_BITS_PER_WIDE_INT == 64
      if ((INTVAL (op) >> 31) != 0 && (INTVAL (op) >> 31) != -1
	  && mask64_operand (op, mode))
	return 2;
      else
#endif
	return num_insns_constant_wide (INTVAL (op));

      case CONST_DOUBLE:
	if (mode == SFmode)
	  {
	    long l;
	    REAL_VALUE_TYPE rv;

	    REAL_VALUE_FROM_CONST_DOUBLE (rv, op);
	    REAL_VALUE_TO_TARGET_SINGLE (rv, l);
	    return num_insns_constant_wide ((HOST_WIDE_INT) l);
	  }

	if (mode == VOIDmode || mode == DImode)
	  {
	    high = CONST_DOUBLE_HIGH (op);
	    low  = CONST_DOUBLE_LOW (op);
	  }
	else
	  {
	    long l[2];
	    REAL_VALUE_TYPE rv;

	    REAL_VALUE_FROM_CONST_DOUBLE (rv, op);
	    REAL_VALUE_TO_TARGET_DOUBLE (rv, l);
	    high = l[WORDS_BIG_ENDIAN == 0];
	    low  = l[WORDS_BIG_ENDIAN != 0];
	  }

	if (TARGET_32BIT)
	  return (num_insns_constant_wide (low)
		  + num_insns_constant_wide (high));
	else
	  {
	    if ((high == 0 && low >= 0)
		|| (high == -1 && low < 0))
	      return num_insns_constant_wide (low);

	    else if (mask64_operand (op, mode))
	      return 2;

	    else if (low == 0)
	      return num_insns_constant_wide (high) + 1;

	    else
	      return (num_insns_constant_wide (high)
		      + num_insns_constant_wide (low) + 1);
	  }

    default:
      gcc_unreachable ();
    }
}