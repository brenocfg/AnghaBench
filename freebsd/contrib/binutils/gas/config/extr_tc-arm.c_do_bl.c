#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_ARM_PCREL_BRANCH ; 
 int /*<<< orphan*/  BFD_RELOC_ARM_PCREL_CALL ; 
 int /*<<< orphan*/  BFD_RELOC_ARM_PCREL_JUMP ; 
 scalar_t__ COND_ALWAYS ; 
 scalar_t__ EF_ARM_EABI_VER4 ; 
 scalar_t__ EF_ARM_EABI_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_branch (int /*<<< orphan*/ ) ; 
 TYPE_1__ inst ; 
 int /*<<< orphan*/  meabi_flags ; 

__attribute__((used)) static void
do_bl (void)
{
#ifdef OBJ_ELF
  if (EF_ARM_EABI_VERSION (meabi_flags) >= EF_ARM_EABI_VER4)
    {
      if (inst.cond == COND_ALWAYS)
	encode_branch (BFD_RELOC_ARM_PCREL_CALL);
      else
	encode_branch (BFD_RELOC_ARM_PCREL_JUMP);
    }
  else
#endif
    encode_branch (BFD_RELOC_ARM_PCREL_BRANCH);
}