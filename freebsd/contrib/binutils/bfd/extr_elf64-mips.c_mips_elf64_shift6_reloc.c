#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_6__ {int addend; TYPE_1__* howto; } ;
typedef  TYPE_2__ arelent ;
struct TYPE_5__ {scalar_t__ partial_inplace; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_mips_elf_generic_reloc (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static bfd_reloc_status_type
mips_elf64_shift6_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
			 void *data, asection *input_section, bfd *output_bfd,
			 char **error_message)
{
  if (reloc_entry->howto->partial_inplace)
    {
      reloc_entry->addend = ((reloc_entry->addend & 0x00007c0)
			     | (reloc_entry->addend & 0x00000800) >> 9);
    }

  return _bfd_mips_elf_generic_reloc (abfd, reloc_entry, symbol, data,
				      input_section, output_bfd,
				      error_message);
}