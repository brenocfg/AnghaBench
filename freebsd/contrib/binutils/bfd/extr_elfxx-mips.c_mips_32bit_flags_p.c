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
typedef  int flagword ;
typedef  int bfd_boolean ;

/* Variables and functions */
 int EF_MIPS_32BITMODE ; 
 int EF_MIPS_ABI ; 
 int EF_MIPS_ARCH ; 
 int E_MIPS_ABI_EABI32 ; 
 int E_MIPS_ABI_O32 ; 
 int E_MIPS_ARCH_1 ; 
 int E_MIPS_ARCH_2 ; 
 int E_MIPS_ARCH_32 ; 
 int E_MIPS_ARCH_32R2 ; 

__attribute__((used)) static bfd_boolean
mips_32bit_flags_p (flagword flags)
{
  return ((flags & EF_MIPS_32BITMODE) != 0
	  || (flags & EF_MIPS_ABI) == E_MIPS_ABI_O32
	  || (flags & EF_MIPS_ABI) == E_MIPS_ABI_EABI32
	  || (flags & EF_MIPS_ARCH) == E_MIPS_ARCH_1
	  || (flags & EF_MIPS_ARCH) == E_MIPS_ARCH_2
	  || (flags & EF_MIPS_ARCH) == E_MIPS_ARCH_32
	  || (flags & EF_MIPS_ARCH) == E_MIPS_ARCH_32R2);
}