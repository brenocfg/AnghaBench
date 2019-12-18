#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {int intoffset; int words; int use_stack; } ;
typedef  int HOST_WIDE_INT ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int BITS_PER_WORD ; 
 int BLKmode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GP_ARG_MIN_REG ; 
 int GP_ARG_NUM_REG ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  MODE_INT ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,unsigned int) ; 
 int mode_for_size (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int word_mode ; 

__attribute__((used)) static void
rs6000_darwin64_record_arg_flush (CUMULATIVE_ARGS *cum,
				  HOST_WIDE_INT bitpos, rtx rvec[], int *k)
{
  enum machine_mode mode;
  unsigned int regno;
  unsigned int startbit, endbit;
  int this_regno, intregs, intoffset;
  rtx reg;

  if (cum->intoffset == -1)
    return;

  intoffset = cum->intoffset;
  cum->intoffset = -1;

  /* If this is the trailing part of a word, try to only load that
     much into the register.  Otherwise load the whole register.  Note
     that in the latter case we may pick up unwanted bits.  It's not a
     problem at the moment but may wish to revisit.  */

  if (intoffset % BITS_PER_WORD != 0)
    {
      mode = mode_for_size (BITS_PER_WORD - intoffset % BITS_PER_WORD,
			  MODE_INT, 0);
      if (mode == BLKmode)
	{
	  /* We couldn't find an appropriate mode, which happens,
	     e.g., in packed structs when there are 3 bytes to load.
	     Back intoffset back to the beginning of the word in this
	     case.  */
	 intoffset = intoffset & -BITS_PER_WORD;
	 mode = word_mode;
	}
    }
  else
    mode = word_mode;

  startbit = intoffset & -BITS_PER_WORD;
  endbit = (bitpos + BITS_PER_WORD - 1) & -BITS_PER_WORD;
  intregs = (endbit - startbit) / BITS_PER_WORD;
  this_regno = cum->words + intoffset / BITS_PER_WORD;

  if (intregs > 0 && intregs > GP_ARG_NUM_REG - this_regno)
    cum->use_stack = 1;

  intregs = MIN (intregs, GP_ARG_NUM_REG - this_regno);
  if (intregs <= 0)
    return;

  intoffset /= BITS_PER_UNIT;
  do
    {
      regno = GP_ARG_MIN_REG + this_regno;
      reg = gen_rtx_REG (mode, regno);
      rvec[(*k)++] =
	gen_rtx_EXPR_LIST (VOIDmode, reg, GEN_INT (intoffset));

      this_regno += 1;
      intoffset = (intoffset | (UNITS_PER_WORD-1)) + 1;
      mode = word_mode;
      intregs -= 1;
    }
  while (intregs > 0);
}