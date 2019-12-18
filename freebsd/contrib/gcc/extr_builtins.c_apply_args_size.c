#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_6__ {int /*<<< orphan*/  decl; } ;
struct TYPE_4__ {scalar_t__ (* struct_value_rtx ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ calls; } ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int CEIL (int,int) ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ FUNCTION_ARG_REGNO_P (unsigned int) ; 
 int GET_MODE_ALIGNMENT (int) ; 
 int GET_MODE_SIZE (int) ; 
 int Pmode ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int* apply_args_mode ; 
 int* apply_args_reg_offset ; 
 TYPE_3__* cfun ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int* reg_raw_mode ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static int
apply_args_size (void)
{
  static int size = -1;
  int align;
  unsigned int regno;
  enum machine_mode mode;

  /* The values computed by this function never change.  */
  if (size < 0)
    {
      /* The first value is the incoming arg-pointer.  */
      size = GET_MODE_SIZE (Pmode);

      /* The second value is the structure value address unless this is
	 passed as an "invisible" first argument.  */
      if (targetm.calls.struct_value_rtx (cfun ? TREE_TYPE (cfun->decl) : 0, 0))
	size += GET_MODE_SIZE (Pmode);

      for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
	if (FUNCTION_ARG_REGNO_P (regno))
	  {
	    mode = reg_raw_mode[regno];

	    gcc_assert (mode != VOIDmode);

	    align = GET_MODE_ALIGNMENT (mode) / BITS_PER_UNIT;
	    if (size % align != 0)
	      size = CEIL (size, align) * align;
	    apply_args_reg_offset[regno] = size;
	    size += GET_MODE_SIZE (mode);
	    apply_args_mode[regno] = mode;
	  }
	else
	  {
	    apply_args_mode[regno] = VOIDmode;
	    apply_args_reg_offset[regno] = 0;
	  }
    }
  return size;
}