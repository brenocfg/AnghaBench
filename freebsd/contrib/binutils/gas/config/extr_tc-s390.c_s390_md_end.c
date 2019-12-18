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
 int /*<<< orphan*/  bfd_arch_s390 ; 
 int /*<<< orphan*/  bfd_mach_s390_31 ; 
 int /*<<< orphan*/  bfd_mach_s390_64 ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s390_arch_size ; 
 int /*<<< orphan*/  stdoutput ; 

void
s390_md_end ()
{
  if (s390_arch_size == 64)
    bfd_set_arch_mach (stdoutput, bfd_arch_s390, bfd_mach_s390_64);
  else
    bfd_set_arch_mach (stdoutput, bfd_arch_s390, bfd_mach_s390_31);
}