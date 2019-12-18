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
 int /*<<< orphan*/  fp_consts_inited ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  init_fp_table () ; 
 char const** strings_fp ; 
 int /*<<< orphan*/ * values_fp ; 

const char *
fp_immediate_constant (rtx x)
{
  REAL_VALUE_TYPE r;
  int i;

  if (!fp_consts_inited)
    init_fp_table ();

  REAL_VALUE_FROM_CONST_DOUBLE (r, x);
  for (i = 0; i < 8; i++)
    if (REAL_VALUES_EQUAL (r, values_fp[i]))
      return strings_fp[i];

  gcc_unreachable ();
}