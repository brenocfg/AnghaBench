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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ REAL_VALUES_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_VALUE_MINUS_ZERO (int /*<<< orphan*/ ) ; 
 int fp_consts_inited ; 
 int /*<<< orphan*/  init_fp_table () ; 
 int /*<<< orphan*/ * values_fp ; 

int
arm_const_double_rtx (rtx x)
{
  REAL_VALUE_TYPE r;
  int i;

  if (!fp_consts_inited)
    init_fp_table ();

  REAL_VALUE_FROM_CONST_DOUBLE (r, x);
  if (REAL_VALUE_MINUS_ZERO (r))
    return 0;

  for (i = 0; i < fp_consts_inited; i++)
    if (REAL_VALUES_EQUAL (r, values_fp[i]))
      return 1;

  return 0;
}