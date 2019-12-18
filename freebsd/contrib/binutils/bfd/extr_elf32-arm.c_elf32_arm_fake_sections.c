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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_3__ {int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  SHF_LINK_ORDER ; 
 int /*<<< orphan*/  SHT_ARM_EXIDX ; 
 int /*<<< orphan*/  TRUE ; 
 char* bfd_get_section_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_arm_elf_unwind_section_name (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bfd_boolean
elf32_arm_fake_sections (bfd * abfd, Elf_Internal_Shdr * hdr, asection * sec)
{
  const char * name;

  name = bfd_get_section_name (abfd, sec);

  if (is_arm_elf_unwind_section_name (abfd, name))
    {
      hdr->sh_type = SHT_ARM_EXIDX;
      hdr->sh_flags |= SHF_LINK_ORDER;
    }
  return TRUE;
}