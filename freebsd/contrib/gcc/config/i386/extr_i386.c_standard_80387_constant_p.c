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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ CONST0_RTX (scalar_t__) ; 
 scalar_t__ CONST1_RTX (scalar_t__) ; 
 scalar_t__ CONST_DOUBLE ; 
 int /*<<< orphan*/  FLOAT_MODE_P (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,scalar_t__) ; 
 int TUNEMASK ; 
 scalar_t__ XFmode ; 
 int /*<<< orphan*/  ext_80387_constants_init ; 
 int /*<<< orphan*/ * ext_80387_constants_table ; 
 int /*<<< orphan*/  init_ext_80387_constants () ; 
 scalar_t__ optimize_size ; 
 scalar_t__ real_identical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int x86_ext_80387_constants ; 

int
standard_80387_constant_p (rtx x)
{
  if (GET_CODE (x) != CONST_DOUBLE || !FLOAT_MODE_P (GET_MODE (x)))
    return -1;

  if (x == CONST0_RTX (GET_MODE (x)))
    return 1;
  if (x == CONST1_RTX (GET_MODE (x)))
    return 2;

  /* For XFmode constants, try to find a special 80387 instruction when
     optimizing for size or on those CPUs that benefit from them.  */
  if (GET_MODE (x) == XFmode
      && (optimize_size || x86_ext_80387_constants & TUNEMASK))
    {
      REAL_VALUE_TYPE r;
      int i;

      if (! ext_80387_constants_init)
	init_ext_80387_constants ();

      REAL_VALUE_FROM_CONST_DOUBLE (r, x);
      for (i = 0; i < 5; i++)
        if (real_identical (&r, &ext_80387_constants_table[i]))
	  return i + 3;
    }

  return 0;
}