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
typedef  scalar_t__ tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  CUMULATIVE_ARGS ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (scalar_t__) ; 
 int BLKmode ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GET_MODE_SIZE (int) ; 
 scalar_t__ MODE_COMPLEX_FLOAT ; 
 scalar_t__ MODE_COMPLEX_INT ; 
 int ROUND_ADVANCE (int) ; 
 int SPARC_FP_ARG_MAX ; 
 int SPARC_INT_ARG_MAX ; 
 scalar_t__ TARGET_ARCH32 ; 
 scalar_t__ TARGET_FPU ; 
 int UNITS_PER_WORD ; 
 int function_arg_slotno (int /*<<< orphan*/ *,int,scalar_t__,int,int /*<<< orphan*/ ,int*,int*) ; 
 int int_size_in_bytes (scalar_t__) ; 

__attribute__((used)) static int
sparc_arg_partial_bytes (CUMULATIVE_ARGS *cum, enum machine_mode mode,
			 tree type, bool named)
{
  int slotno, regno, padding;

  /* We pass 0 for incoming_p here, it doesn't matter.  */
  slotno = function_arg_slotno (cum, mode, type, named, 0, &regno, &padding);

  if (slotno == -1)
    return 0;

  if (TARGET_ARCH32)
    {
      if ((slotno + (mode == BLKmode
		     ? ROUND_ADVANCE (int_size_in_bytes (type))
		     : ROUND_ADVANCE (GET_MODE_SIZE (mode))))
	  > SPARC_INT_ARG_MAX)
	return (SPARC_INT_ARG_MAX - slotno) * UNITS_PER_WORD;
    }
  else
    {
      /* We are guaranteed by pass_by_reference that the size of the
	 argument is not greater than 16 bytes, so we only need to return
	 one word if the argument is partially passed in registers.  */

      if (type && AGGREGATE_TYPE_P (type))
	{
	  int size = int_size_in_bytes (type);

	  if (size > UNITS_PER_WORD
	      && slotno == SPARC_INT_ARG_MAX - 1)
	    return UNITS_PER_WORD;
	}
      else if (GET_MODE_CLASS (mode) == MODE_COMPLEX_INT
	       || (GET_MODE_CLASS (mode) == MODE_COMPLEX_FLOAT
		   && ! (TARGET_FPU && named)))
	{
	  /* The complex types are passed as packed types.  */
	  if (GET_MODE_SIZE (mode) > UNITS_PER_WORD
	      && slotno == SPARC_INT_ARG_MAX - 1)
	    return UNITS_PER_WORD;
	}
      else if (GET_MODE_CLASS (mode) == MODE_COMPLEX_FLOAT)
	{
	  if ((slotno + GET_MODE_SIZE (mode) / UNITS_PER_WORD)
	      > SPARC_FP_ARG_MAX)
	    return UNITS_PER_WORD;
	}
    }

  return 0;
}