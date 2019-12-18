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
 int S390_OPCODE_ESA ; 
 unsigned int S390_OPCODE_G5 ; 
 unsigned int S390_OPCODE_Z900 ; 
 int S390_OPCODE_ZARCH ; 
 int /*<<< orphan*/  as_fatal (char*) ; 
 unsigned int current_cpu ; 
 int current_mode_mask ; 
 int /*<<< orphan*/  default_arch ; 
 int s390_arch_size ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
init_default_arch ()
{
  if (strcmp (default_arch, "s390") == 0)
    {
      if (s390_arch_size == 0)
	s390_arch_size = 32;
    }
  else if (strcmp (default_arch, "s390x") == 0)
    {
      if (s390_arch_size == 0)
	s390_arch_size = 64;
    }
  else
    as_fatal ("Invalid default architecture, broken assembler.");

  if (current_mode_mask == 0)
    {
      if (s390_arch_size == 32)
	current_mode_mask = 1 << S390_OPCODE_ESA;
      else
	current_mode_mask = 1 << S390_OPCODE_ZARCH;
    }
  if (current_cpu == -1U)
    {
      if (current_mode_mask == (1 << S390_OPCODE_ESA))
	current_cpu = S390_OPCODE_G5;
      else
	current_cpu = S390_OPCODE_Z900;
    }
}