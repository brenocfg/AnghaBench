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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE_SIZE (int) ; 
 scalar_t__ MAYBE_FLOAT_CLASS_P (int) ; 
 scalar_t__ MAYBE_MMX_CLASS_P (int) ; 
 scalar_t__ MAYBE_SSE_CLASS_P (int) ; 

bool
ix86_cannot_change_mode_class (enum machine_mode from, enum machine_mode to,
			       enum reg_class class)
{
  if (from == to)
    return false;

  /* x87 registers can't do subreg at all, as all values are reformatted
     to extended precision.  */
  if (MAYBE_FLOAT_CLASS_P (class))
    return true;

  if (MAYBE_SSE_CLASS_P (class) || MAYBE_MMX_CLASS_P (class))
    {
      /* Vector registers do not support QI or HImode loads.  If we don't
	 disallow a change to these modes, reload will assume it's ok to
	 drop the subreg from (subreg:SI (reg:HI 100) 0).  This affects
	 the vec_dupv4hi pattern.  */
      if (GET_MODE_SIZE (from) < 4)
	return true;

      /* Vector registers do not support subreg with nonzero offsets, which
	 are otherwise valid for integer registers.  Since we can't see
	 whether we have a nonzero offset from here, prohibit all
         nonparadoxical subregs changing size.  */
      if (GET_MODE_SIZE (to) < GET_MODE_SIZE (from))
	return true;
    }

  return false;
}