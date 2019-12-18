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
 unsigned int FLAGS_REG ; 
 unsigned int FPSR_REG ; 

__attribute__((used)) static bool
ix86_fixed_condition_code_regs (unsigned int *p1, unsigned int *p2)
{
  *p1 = FLAGS_REG;
  *p2 = FPSR_REG;
  return true;
}