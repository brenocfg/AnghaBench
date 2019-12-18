#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {scalar_t__ sh_type; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SHT_X86_64_UNWIND ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_make_section_from_shdr (int /*<<< orphan*/ *,TYPE_1__*,char const*,int) ; 

__attribute__((used)) static bfd_boolean
elf64_x86_64_section_from_shdr (bfd *abfd,
				Elf_Internal_Shdr *hdr,
				const char *name,
				int shindex)
{
  if (hdr->sh_type != SHT_X86_64_UNWIND)
    return FALSE;

  if (! _bfd_elf_make_section_from_shdr (abfd, hdr, name, shindex))
    return FALSE;

  return TRUE;
}