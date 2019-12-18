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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DFmode ; 
 int /*<<< orphan*/  REAL_VALUE_ATOF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_VFP ; 
 int fp_consts_inited ; 
 int /*<<< orphan*/ * strings_fp ; 
 int /*<<< orphan*/ * values_fp ; 

__attribute__((used)) static void
init_fp_table (void)
{
  int i;
  REAL_VALUE_TYPE r;

  if (TARGET_VFP)
    fp_consts_inited = 1;
  else
    fp_consts_inited = 8;

  for (i = 0; i < fp_consts_inited; i++)
    {
      r = REAL_VALUE_ATOF (strings_fp[i], DFmode);
      values_fp[i] = r;
    }
}