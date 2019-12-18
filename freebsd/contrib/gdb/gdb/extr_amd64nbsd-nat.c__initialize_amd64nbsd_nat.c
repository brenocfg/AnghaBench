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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd64_native_gregset32_num_regs ; 
 int /*<<< orphan*/  amd64_native_gregset32_reg_offset ; 
 int /*<<< orphan*/  amd64_native_gregset64_reg_offset ; 
 int /*<<< orphan*/  amd64nbsd32_r_reg_offset ; 
 int /*<<< orphan*/  amd64nbsd_r_reg_offset ; 

void
_initialize_amd64nbsd_nat (void)
{
  amd64_native_gregset32_reg_offset = amd64nbsd32_r_reg_offset;
  amd64_native_gregset32_num_regs = ARRAY_SIZE (amd64nbsd32_r_reg_offset);
  amd64_native_gregset64_reg_offset = amd64nbsd_r_reg_offset;
}