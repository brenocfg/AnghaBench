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
#define  SPARC_OPCODE_ARCH_SPARCLET 131 
#define  SPARC_OPCODE_ARCH_V9 130 
#define  SPARC_OPCODE_ARCH_V9A 129 
#define  SPARC_OPCODE_ARCH_V9B 128 
 int /*<<< orphan*/  bfd_arch_sparc ; 
 unsigned long bfd_mach_sparc ; 
 unsigned long bfd_mach_sparc_sparclet ; 
 unsigned long bfd_mach_sparc_v8plus ; 
 unsigned long bfd_mach_sparc_v8plusa ; 
 unsigned long bfd_mach_sparc_v8plusb ; 
 unsigned long bfd_mach_sparc_v9 ; 
 unsigned long bfd_mach_sparc_v9a ; 
 unsigned long bfd_mach_sparc_v9b ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int current_architecture ; 
 int sparc_arch_size ; 
 int /*<<< orphan*/  stdoutput ; 

void
sparc_md_end ()
{
  unsigned long mach = bfd_mach_sparc;

  if (sparc_arch_size == 64)
    switch (current_architecture)
      {
      case SPARC_OPCODE_ARCH_V9A: mach = bfd_mach_sparc_v9a; break;
      case SPARC_OPCODE_ARCH_V9B: mach = bfd_mach_sparc_v9b; break;
      default: mach = bfd_mach_sparc_v9; break;
      }
  else
    switch (current_architecture)
      {
      case SPARC_OPCODE_ARCH_SPARCLET: mach = bfd_mach_sparc_sparclet; break;
      case SPARC_OPCODE_ARCH_V9: mach = bfd_mach_sparc_v8plus; break;
      case SPARC_OPCODE_ARCH_V9A: mach = bfd_mach_sparc_v8plusa; break;
      case SPARC_OPCODE_ARCH_V9B: mach = bfd_mach_sparc_v8plusb; break;
      /* The sparclite is treated like a normal sparc.  Perhaps it shouldn't
	 be but for now it is (since that's the way it's always been
	 treated).  */
      default: break;
      }
  bfd_set_arch_mach (stdoutput, bfd_arch_sparc, mach);
}