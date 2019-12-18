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
typedef  int /*<<< orphan*/  flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int sh_flags; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_SMALL_DATA ; 
 int SHF_ALPHA_GPREL ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
elf64_alpha_section_flags (flagword *flags, const Elf_Internal_Shdr *hdr)
{
  if (hdr->sh_flags & SHF_ALPHA_GPREL)
    *flags |= SEC_SMALL_DATA;

  return TRUE;
}