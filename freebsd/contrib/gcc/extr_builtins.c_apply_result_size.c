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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int APPLY_RESULT_SIZE ; 
 int BITS_PER_UNIT ; 
 int CEIL (int,int) ; 
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ FUNCTION_VALUE_REGNO_P (int) ; 
 int GET_MODE_ALIGNMENT (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int VOIDmode ; 
 int* apply_result_mode ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int* reg_raw_mode ; 

__attribute__((used)) static int
apply_result_size (void)
{
  static int size = -1;
  int align, regno;
  enum machine_mode mode;

  /* The values computed by this function never change.  */
  if (size < 0)
    {
      size = 0;

      for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
	if (FUNCTION_VALUE_REGNO_P (regno))
	  {
	    mode = reg_raw_mode[regno];

	    gcc_assert (mode != VOIDmode);

	    align = GET_MODE_ALIGNMENT (mode) / BITS_PER_UNIT;
	    if (size % align != 0)
	      size = CEIL (size, align) * align;
	    size += GET_MODE_SIZE (mode);
	    apply_result_mode[regno] = mode;
	  }
	else
	  apply_result_mode[regno] = VOIDmode;

      /* Allow targets that use untyped_call and untyped_return to override
	 the size so that machine-specific information can be stored here.  */
#ifdef APPLY_RESULT_SIZE
      size = APPLY_RESULT_SIZE;
#endif
    }
  return size;
}