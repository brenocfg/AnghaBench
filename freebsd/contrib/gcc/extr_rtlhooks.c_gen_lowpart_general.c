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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ BYTES_BIG_ENDIAN ; 
 scalar_t__ FLOAT_MODE_P (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int MAX (scalar_t__,scalar_t__) ; 
 int MEM_P (scalar_t__) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SCALAR_INT_MODE_P (int) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ TRULY_NOOP_TRUNCATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 scalar_t__ adjust_address (scalar_t__,int,int) ; 
 scalar_t__ copy_to_reg (scalar_t__) ; 
 scalar_t__ force_reg (int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gen_lowpart_common (int,scalar_t__) ; 
 int /*<<< orphan*/  no_new_pseudos ; 

rtx
gen_lowpart_general (enum machine_mode mode, rtx x)
{
  rtx result = gen_lowpart_common (mode, x);

  if (result)
    return result;
  /* If it's a REG, it must be a hard reg that's not valid in MODE.  */
  else if (REG_P (x)
	   /* Or we could have a subreg of a floating point value.  */
	   || (GET_CODE (x) == SUBREG
	       && FLOAT_MODE_P (GET_MODE (SUBREG_REG (x)))))
    {
      result = gen_lowpart_common (mode, copy_to_reg (x));
      gcc_assert (result != 0);
      return result;
    }
  else
    {
      int offset = 0;

      /* The only additional case we can do is MEM.  */
      gcc_assert (MEM_P (x));

      /* The following exposes the use of "x" to CSE.  */
      if (GET_MODE_SIZE (GET_MODE (x)) <= UNITS_PER_WORD
	  && SCALAR_INT_MODE_P (GET_MODE (x))
	  && TRULY_NOOP_TRUNCATION (GET_MODE_BITSIZE (mode),
				    GET_MODE_BITSIZE (GET_MODE (x)))
	  && ! no_new_pseudos)
	return gen_lowpart_general (mode, force_reg (GET_MODE (x), x));

      if (WORDS_BIG_ENDIAN)
	offset = (MAX (GET_MODE_SIZE (GET_MODE (x)), UNITS_PER_WORD)
		  - MAX (GET_MODE_SIZE (mode), UNITS_PER_WORD));

      if (BYTES_BIG_ENDIAN)
	/* Adjust the address so that the address-after-the-data
	   is unchanged.  */
	offset -= (MIN (UNITS_PER_WORD, GET_MODE_SIZE (mode))
		   - MIN (UNITS_PER_WORD, GET_MODE_SIZE (GET_MODE (x))));

      return adjust_address (x, mode, offset);
    }
}