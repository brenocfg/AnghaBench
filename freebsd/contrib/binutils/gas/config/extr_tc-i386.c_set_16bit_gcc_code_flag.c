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
 int CODE_64BIT ; 
 int Cpu64 ; 
 int CpuNo64 ; 
 int /*<<< orphan*/  LONG_MNEM_SUFFIX ; 
 int cpu_arch_flags ; 
 int flag_code ; 
 int /*<<< orphan*/  stackop_size ; 

__attribute__((used)) static void
set_16bit_gcc_code_flag (int new_code_flag)
{
  flag_code = new_code_flag;
  cpu_arch_flags &= ~(Cpu64 | CpuNo64);
  cpu_arch_flags |= (flag_code == CODE_64BIT ? Cpu64 : CpuNo64);
  stackop_size = LONG_MNEM_SUFFIX;
}