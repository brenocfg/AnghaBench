#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {scalar_t__ sh_type; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 int SEC_LINK_DUPLICATES_SAME_CONTENTS ; 
 int SEC_LINK_ONCE ; 
 scalar_t__ SHT_NOTE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
elf32_arm_section_flags (flagword *flags, const Elf_Internal_Shdr *hdr)
{
  if (hdr->sh_type == SHT_NOTE)
    *flags |= SEC_LINK_ONCE | SEC_LINK_DUPLICATES_SAME_CONTENTS;

  return TRUE;
}