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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHEAP_REGNO (unsigned int) ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 unsigned int REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SMALL_REGISTER_CLASSES ; 

__attribute__((used)) static int
approx_reg_cost_1 (rtx *xp, void *data)
{
  rtx x = *xp;
  int *cost_p = data;

  if (x && REG_P (x))
    {
      unsigned int regno = REGNO (x);

      if (! CHEAP_REGNO (regno))
	{
	  if (regno < FIRST_PSEUDO_REGISTER)
	    {
	      if (SMALL_REGISTER_CLASSES)
		return 1;
	      *cost_p += 2;
	    }
	  else
	    *cost_p += 1;
	}
    }

  return 0;
}