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
#define  EF_MEP_CPU_C2 131 
#define  EF_MEP_CPU_C3 130 
#define  EF_MEP_CPU_C4 129 
#define  EF_MEP_CPU_H1 128 
 int MEP_CPU ; 
 int bfd_mach_mep ; 
 int bfd_mach_mep_h1 ; 

__attribute__((used)) static int
mep_machine (void)
{
  switch (MEP_CPU)
    {
    default: break;
    case EF_MEP_CPU_C2: return bfd_mach_mep;
    case EF_MEP_CPU_C3: return bfd_mach_mep;
    case EF_MEP_CPU_C4: return bfd_mach_mep;
    case EF_MEP_CPU_H1: return bfd_mach_mep_h1;
    }

  return bfd_mach_mep;
}