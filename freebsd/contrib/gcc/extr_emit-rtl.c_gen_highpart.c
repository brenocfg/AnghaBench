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
typedef  int rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 scalar_t__ GET_MODE_UNIT_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int) ; 
 unsigned int UNITS_PER_WORD ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int simplify_gen_subreg (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreg_highpart_offset (int,int /*<<< orphan*/ ) ; 
 int validize_mem (int) ; 

rtx
gen_highpart (enum machine_mode mode, rtx x)
{
  unsigned int msize = GET_MODE_SIZE (mode);
  rtx result;

  /* This case loses if X is a subreg.  To catch bugs early,
     complain if an invalid MODE is used even in other cases.  */
  gcc_assert (msize <= UNITS_PER_WORD
	      || msize == (unsigned int) GET_MODE_UNIT_SIZE (GET_MODE (x)));

  result = simplify_gen_subreg (mode, x, GET_MODE (x),
				subreg_highpart_offset (mode, GET_MODE (x)));
  gcc_assert (result);
  
  /* simplify_gen_subreg is not guaranteed to return a valid operand for
     the target if we have a MEM.  gen_highpart must return a valid operand,
     emitting code if necessary to do so.  */
  if (MEM_P (result))
    {
      result = validize_mem (result);
      gcc_assert (result);
    }
  
  return result;
}