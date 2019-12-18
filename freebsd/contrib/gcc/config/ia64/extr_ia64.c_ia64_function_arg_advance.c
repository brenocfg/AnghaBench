#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_4__ {int words; int fp_regs; int int_regs; scalar_t__ prototype; } ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 int BLKmode ; 
 int /*<<< orphan*/  FLOAT_MODE_P (int) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GET_MODE_SIZE (int) ; 
 int MAX_ARGUMENT_SLOTS ; 
 scalar_t__ MODE_COMPLEX_FLOAT ; 
 int TCmode ; 
 int TFmode ; 
 int UNITS_PER_WORD ; 
 int VOIDmode ; 
 int hfa_element_mode (scalar_t__,int /*<<< orphan*/ ) ; 
 int ia64_function_arg_offset (TYPE_1__*,scalar_t__,int) ; 
 int ia64_function_arg_words (scalar_t__,int) ; 
 int int_size_in_bytes (scalar_t__) ; 

void
ia64_function_arg_advance (CUMULATIVE_ARGS *cum, enum machine_mode mode,
			   tree type, int named)
{
  int words = ia64_function_arg_words (type, mode);
  int offset = ia64_function_arg_offset (cum, type, words);
  enum machine_mode hfa_mode = VOIDmode;

  /* If all arg slots are already full, then there is nothing to do.  */
  if (cum->words >= MAX_ARGUMENT_SLOTS)
    return;

  cum->words += words + offset;

  /* Check for and handle homogeneous FP aggregates.  */
  if (type)
    hfa_mode = hfa_element_mode (type, 0);

  /* Unnamed prototyped hfas are passed as usual.  Named prototyped hfas
     and unprototyped hfas are passed specially.  */
  if (hfa_mode != VOIDmode && (! cum->prototype || named))
    {
      int fp_regs = cum->fp_regs;
      /* This is the original value of cum->words + offset.  */
      int int_regs = cum->words - words;
      int hfa_size = GET_MODE_SIZE (hfa_mode);
      int byte_size;
      int args_byte_size;

      /* If prototyped, pass it in FR regs then GR regs.
	 If not prototyped, pass it in both FR and GR regs.

	 If this is an SFmode aggregate, then it is possible to run out of
	 FR regs while GR regs are still left.  In that case, we pass the
	 remaining part in the GR regs.  */

      /* Fill the FP regs.  We do this always.  We stop if we reach the end
	 of the argument, the last FP register, or the last argument slot.  */

      byte_size = ((mode == BLKmode)
		   ? int_size_in_bytes (type) : GET_MODE_SIZE (mode));
      args_byte_size = int_regs * UNITS_PER_WORD;
      offset = 0;
      for (; (offset < byte_size && fp_regs < MAX_ARGUMENT_SLOTS
	      && args_byte_size < (MAX_ARGUMENT_SLOTS * UNITS_PER_WORD));)
	{
	  offset += hfa_size;
	  args_byte_size += hfa_size;
	  fp_regs++;
	}

      cum->fp_regs = fp_regs;
    }

  /* Integral and aggregates go in general registers.  So do TFmode FP values.
     If we have run out of FR registers, then other FP values must also go in
     general registers.  This can happen when we have a SFmode HFA.  */
  else if (mode == TFmode || mode == TCmode
           || (! FLOAT_MODE_P (mode) || cum->fp_regs == MAX_ARGUMENT_SLOTS))
    cum->int_regs = cum->words;

  /* If there is a prototype, then FP values go in a FR register when
     named, and in a GR register when unnamed.  */
  else if (cum->prototype)
    {
      if (! named)
	cum->int_regs = cum->words;
      else
	/* ??? Complex types should not reach here.  */
	cum->fp_regs += (GET_MODE_CLASS (mode) == MODE_COMPLEX_FLOAT ? 2 : 1);
    }
  /* If there is no prototype, then FP values go in both FR and GR
     registers.  */
  else
    {
      /* ??? Complex types should not reach here.  */
      cum->fp_regs += (GET_MODE_CLASS (mode) == MODE_COMPLEX_FLOAT ? 2 : 1);
      cum->int_regs = cum->words;
    }
}