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
 scalar_t__ bfd_arch_rs6000 ; 
 unsigned long bfd_mach_ppc ; 
 unsigned long bfd_mach_ppc64 ; 
 unsigned long bfd_mach_rs6k ; 
 scalar_t__ ppc_arch () ; 
 scalar_t__ ppc_obj64 ; 

unsigned long
ppc_mach (void)
{
  if (ppc_obj64)
    return bfd_mach_ppc64;
  else if (ppc_arch () == bfd_arch_rs6000)
    return bfd_mach_rs6k;
  else
    return bfd_mach_ppc;
}