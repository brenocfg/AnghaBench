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
typedef  scalar_t__ tree ;
struct mips_arg_info {int fpr_p; int reg_offset; int stack_offset; scalar_t__ reg_words; scalar_t__ stack_words; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {int arg_number; int num_gprs; int num_fprs; int stack_words; int /*<<< orphan*/  gp_reg_found; } ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
#define  ABI_32 132 
#define  ABI_64 131 
#define  ABI_EABI 130 
#define  ABI_N32 129 
#define  ABI_O64 128 
 scalar_t__ BITS_PER_WORD ; 
 int /*<<< orphan*/  FLOAT_TYPE_P (scalar_t__) ; 
 scalar_t__ FUNCTION_ARG_BOUNDARY (int,scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 unsigned int GET_MODE_UNIT_SIZE (int) ; 
 int MAX_ARGS_IN_REGISTERS ; 
 scalar_t__ MIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  MODE_COMPLEX_FLOAT ; 
 int /*<<< orphan*/  MODE_FLOAT ; 
 int /*<<< orphan*/  MODE_VECTOR_FLOAT ; 
 int /*<<< orphan*/  SCALAR_FLOAT_TYPE_P (scalar_t__) ; 
 unsigned int UNITS_PER_FPVALUE ; 
 unsigned int UNITS_PER_WORD ; 
 int /*<<< orphan*/  VECTOR_FLOAT_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 unsigned int int_size_in_bytes (scalar_t__) ; 
 int mips_abi ; 

__attribute__((used)) static void
mips_arg_info (const CUMULATIVE_ARGS *cum, enum machine_mode mode,
	       tree type, int named, struct mips_arg_info *info)
{
  bool doubleword_aligned_p;
  unsigned int num_bytes, num_words, max_regs;

  /* Work out the size of the argument.  */
  num_bytes = type ? int_size_in_bytes (type) : GET_MODE_SIZE (mode);
  num_words = (num_bytes + UNITS_PER_WORD - 1) / UNITS_PER_WORD;

  /* Decide whether it should go in a floating-point register, assuming
     one is free.  Later code checks for availability.

     The checks against UNITS_PER_FPVALUE handle the soft-float and
     single-float cases.  */
  switch (mips_abi)
    {
    case ABI_EABI:
      /* The EABI conventions have traditionally been defined in terms
	 of TYPE_MODE, regardless of the actual type.  */
      info->fpr_p = ((GET_MODE_CLASS (mode) == MODE_FLOAT
		      || GET_MODE_CLASS (mode) == MODE_VECTOR_FLOAT)
		     && GET_MODE_SIZE (mode) <= UNITS_PER_FPVALUE);
      break;

    case ABI_32:
    case ABI_O64:
      /* Only leading floating-point scalars are passed in
	 floating-point registers.  We also handle vector floats the same
	 say, which is OK because they are not covered by the standard ABI.  */
      info->fpr_p = (!cum->gp_reg_found
		     && cum->arg_number < 2
		     && (type == 0 || SCALAR_FLOAT_TYPE_P (type)
			 || VECTOR_FLOAT_TYPE_P (type))
		     && (GET_MODE_CLASS (mode) == MODE_FLOAT
			 || GET_MODE_CLASS (mode) == MODE_VECTOR_FLOAT)
		     && GET_MODE_SIZE (mode) <= UNITS_PER_FPVALUE);
      break;

    case ABI_N32:
    case ABI_64:
      /* Scalar and complex floating-point types are passed in
	 floating-point registers.  */
      info->fpr_p = (named
		     && (type == 0 || FLOAT_TYPE_P (type))
		     && (GET_MODE_CLASS (mode) == MODE_FLOAT
			 || GET_MODE_CLASS (mode) == MODE_COMPLEX_FLOAT
			 || GET_MODE_CLASS (mode) == MODE_VECTOR_FLOAT)
		     && GET_MODE_UNIT_SIZE (mode) <= UNITS_PER_FPVALUE);

      /* ??? According to the ABI documentation, the real and imaginary
	 parts of complex floats should be passed in individual registers.
	 The real and imaginary parts of stack arguments are supposed
	 to be contiguous and there should be an extra word of padding
	 at the end.

	 This has two problems.  First, it makes it impossible to use a
	 single "void *" va_list type, since register and stack arguments
	 are passed differently.  (At the time of writing, MIPSpro cannot
	 handle complex float varargs correctly.)  Second, it's unclear
	 what should happen when there is only one register free.

	 For now, we assume that named complex floats should go into FPRs
	 if there are two FPRs free, otherwise they should be passed in the
	 same way as a struct containing two floats.  */
      if (info->fpr_p
	  && GET_MODE_CLASS (mode) == MODE_COMPLEX_FLOAT
	  && GET_MODE_UNIT_SIZE (mode) < UNITS_PER_FPVALUE)
	{
	  if (cum->num_gprs >= MAX_ARGS_IN_REGISTERS - 1)
	    info->fpr_p = false;
	  else
	    num_words = 2;
	}
      break;

    default:
      gcc_unreachable ();
    }

  /* See whether the argument has doubleword alignment.  */
  doubleword_aligned_p = FUNCTION_ARG_BOUNDARY (mode, type) > BITS_PER_WORD;

  /* Set REG_OFFSET to the register count we're interested in.
     The EABI allocates the floating-point registers separately,
     but the other ABIs allocate them like integer registers.  */
  info->reg_offset = (mips_abi == ABI_EABI && info->fpr_p
		      ? cum->num_fprs
		      : cum->num_gprs);

  /* Advance to an even register if the argument is doubleword-aligned.  */
  if (doubleword_aligned_p)
    info->reg_offset += info->reg_offset & 1;

  /* Work out the offset of a stack argument.  */
  info->stack_offset = cum->stack_words;
  if (doubleword_aligned_p)
    info->stack_offset += info->stack_offset & 1;

  max_regs = MAX_ARGS_IN_REGISTERS - info->reg_offset;

  /* Partition the argument between registers and stack.  */
  info->reg_words = MIN (num_words, max_regs);
  info->stack_words = num_words - info->reg_words;
}