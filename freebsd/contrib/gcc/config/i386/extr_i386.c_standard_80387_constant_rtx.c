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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_DOUBLE_FROM_REAL_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFmode ; 
 int /*<<< orphan*/  ext_80387_constants_init ; 
 int /*<<< orphan*/ * ext_80387_constants_table ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  init_ext_80387_constants () ; 

rtx
standard_80387_constant_rtx (int idx)
{
  int i;

  if (! ext_80387_constants_init)
    init_ext_80387_constants ();

  switch (idx)
    {
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      i = idx - 3;
      break;

    default:
      gcc_unreachable ();
    }

  return CONST_DOUBLE_FROM_REAL_VALUE (ext_80387_constants_table[i],
				       XFmode);
}