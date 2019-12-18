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

/* Variables and functions */
 int FIRST_FLOAT_REG ; 
 int FIRST_MMX_REG ; 
 int FIRST_SSE_REG ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 scalar_t__ TARGET_FLOAT_RETURNS_IN_80387 ; 
 scalar_t__ TARGET_MACHO ; 
 scalar_t__ TARGET_MMX ; 
 scalar_t__ TARGET_SSE ; 

bool
ix86_function_value_regno_p (int regno)
{
  if (TARGET_MACHO)
    {
      if (!TARGET_64BIT)
        {
          return ((regno) == 0
                  || ((regno) == FIRST_FLOAT_REG && TARGET_FLOAT_RETURNS_IN_80387)
                  || ((regno) == FIRST_SSE_REG && TARGET_SSE));
        }
      return ((regno) == 0 || (regno) == FIRST_FLOAT_REG
              || ((regno) == FIRST_SSE_REG && TARGET_SSE)
              || ((regno) == FIRST_FLOAT_REG && TARGET_FLOAT_RETURNS_IN_80387));
      }
  else
    {
      if (regno == 0
          || (regno == FIRST_FLOAT_REG && TARGET_FLOAT_RETURNS_IN_80387)
          || (regno == FIRST_SSE_REG && TARGET_SSE))
        return true;

      if (!TARGET_64BIT
          && (regno == FIRST_MMX_REG && TARGET_MMX))
	    return true;

      return false;
    }
}