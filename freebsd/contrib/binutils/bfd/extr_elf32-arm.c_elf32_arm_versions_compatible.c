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
typedef  int bfd_boolean ;

/* Variables and functions */
 unsigned int EF_ARM_EABI_VER4 ; 
 unsigned int EF_ARM_EABI_VER5 ; 
 int TRUE ; 

__attribute__((used)) static bfd_boolean
elf32_arm_versions_compatible (unsigned iver, unsigned over)
{
  /* v4 and v5 are the same spec before and after it was released,
     so allow mixing them.  */
  if ((iver == EF_ARM_EABI_VER4 && over == EF_ARM_EABI_VER5)
      || (iver == EF_ARM_EABI_VER5 && over == EF_ARM_EABI_VER4))
    return TRUE;

  return (iver == over);
}