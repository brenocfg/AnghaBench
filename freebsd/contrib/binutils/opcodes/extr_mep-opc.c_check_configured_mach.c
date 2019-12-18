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
#define  EF_MEP_CPU_C2 130 
#define  EF_MEP_CPU_C3 129 
#define  EF_MEP_CPU_H1 128 
 int MACH_BASE ; 
 int MACH_H1 ; 
 int MACH_MEP ; 
 int MEP_CPU ; 

__attribute__((used)) static int
check_configured_mach (int machs)
{
  /* All base insns are supported.  */
  int mach = 1 << MACH_BASE;
  switch (MEP_CPU)
    {
    case EF_MEP_CPU_C2:
    case EF_MEP_CPU_C3:
      mach |= (1 << MACH_MEP);
      break;
    case EF_MEP_CPU_H1:
      mach |= (1 << MACH_H1);
      break;
    default:
      break;
    }
  return machs & mach;
}