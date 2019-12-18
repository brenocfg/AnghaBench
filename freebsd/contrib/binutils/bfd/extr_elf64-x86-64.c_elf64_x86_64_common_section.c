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
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int SHF_X86_64_LARGE ; 
 int /*<<< orphan*/  _bfd_elf_large_com_section ; 
 int /*<<< orphan*/ * bfd_com_section_ptr ; 
 int elf_section_flags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static asection *
elf64_x86_64_common_section (asection *sec)
{
  if ((elf_section_flags (sec) & SHF_X86_64_LARGE) == 0)
    return bfd_com_section_ptr;
  else
    return &_bfd_elf_large_com_section;
}