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
typedef  int /*<<< orphan*/  unw_word ;
struct unw_reg_info {scalar_t__ where; int /*<<< orphan*/  when; } ;

/* Variables and functions */
 scalar_t__ UNW_WHERE_SPILL_HOME ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static inline void
spill_next_when (struct unw_reg_info **regp, struct unw_reg_info *lim,
		 unw_word t)
{
  struct unw_reg_info *reg;

  for (reg = *regp; reg <= lim; ++reg)
    {
      if (reg->where == UNW_WHERE_SPILL_HOME)
	{
	  reg->when = t;
	  *regp = reg + 1;
	  return;
	}
    }
  /* Excess spill.  */
  abort ();
}