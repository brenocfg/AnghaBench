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
struct unw_reg_info {scalar_t__ where; unsigned long val; } ;

/* Variables and functions */
 scalar_t__ UNW_WHERE_PSPREL ; 
 scalar_t__ UNW_WHERE_SPILL_HOME ; 

__attribute__((used)) static void
alloc_spill_area (unsigned long *offp, unsigned long regsize,
		  struct unw_reg_info *lo, struct unw_reg_info *hi)
{
  struct unw_reg_info *reg;

  for (reg = hi; reg >= lo; --reg)
    {
      if (reg->where == UNW_WHERE_SPILL_HOME)
	{
	  reg->where = UNW_WHERE_PSPREL;
	  *offp -= regsize;
	  reg->val = *offp;
	}
    }
}