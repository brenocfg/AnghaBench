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
struct decomposition {scalar_t__ start; scalar_t__ end; scalar_t__ base; scalar_t__ safe; scalar_t__ reg_flag; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 struct decomposition decompose (int /*<<< orphan*/ ) ; 
 scalar_t__ frame_pointer_rtx ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  refers_to_regno_for_reload_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ stack_pointer_rtx ; 

__attribute__((used)) static int
immune_p (rtx x, rtx y, struct decomposition ydata)
{
  struct decomposition xdata;

  if (ydata.reg_flag)
    return !refers_to_regno_for_reload_p (ydata.start, ydata.end, x, (rtx*) 0);
  if (ydata.safe)
    return 1;

  gcc_assert (MEM_P (y));
  /* If Y is memory and X is not, Y can't affect X.  */
  if (!MEM_P (x))
    return 1;

  xdata = decompose (x);

  if (! rtx_equal_p (xdata.base, ydata.base))
    {
      /* If bases are distinct symbolic constants, there is no overlap.  */
      if (CONSTANT_P (xdata.base) && CONSTANT_P (ydata.base))
	return 1;
      /* Constants and stack slots never overlap.  */
      if (CONSTANT_P (xdata.base)
	  && (ydata.base == frame_pointer_rtx
	      || ydata.base == hard_frame_pointer_rtx
	      || ydata.base == stack_pointer_rtx))
	return 1;
      if (CONSTANT_P (ydata.base)
	  && (xdata.base == frame_pointer_rtx
	      || xdata.base == hard_frame_pointer_rtx
	      || xdata.base == stack_pointer_rtx))
	return 1;
      /* If either base is variable, we don't know anything.  */
      return 0;
    }

  return (xdata.start >= ydata.end || ydata.start >= xdata.end);
}