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
 int /*<<< orphan*/  MRI_MUL_PRECEDENCE ; 
 size_t O_divide ; 
 size_t O_modulus ; 
 size_t O_multiply ; 
 int /*<<< orphan*/  STANDARD_MUL_PRECEDENCE ; 
 scalar_t__ flag_m68k_mri ; 
 int /*<<< orphan*/ * op_rank ; 

void
expr_set_precedence (void)
{
  if (flag_m68k_mri)
    {
      op_rank[O_multiply] = MRI_MUL_PRECEDENCE;
      op_rank[O_divide] = MRI_MUL_PRECEDENCE;
      op_rank[O_modulus] = MRI_MUL_PRECEDENCE;
    }
  else
    {
      op_rank[O_multiply] = STANDARD_MUL_PRECEDENCE;
      op_rank[O_divide] = STANDARD_MUL_PRECEDENCE;
      op_rank[O_modulus] = STANDARD_MUL_PRECEDENCE;
    }
}