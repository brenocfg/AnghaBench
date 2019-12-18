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
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */

__attribute__((used)) static unsigned int
bfd_arm_vfp11_regno (unsigned int insn, bfd_boolean is_double, unsigned int rx,
                     unsigned int x)
{
  if (is_double)
    return (((insn >> rx) & 0xf) | (((insn >> x) & 1) << 4)) + 32;
  else
    return (((insn >> rx) & 0xf) << 1) | ((insn >> x) & 1);
}