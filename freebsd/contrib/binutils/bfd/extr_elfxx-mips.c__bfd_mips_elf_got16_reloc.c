#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ asymbol ;
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  arelent ;

/* Variables and functions */
 int BSF_GLOBAL ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  _bfd_mips_elf_generic_reloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  _bfd_mips_elf_hi16_reloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  bfd_get_section (TYPE_1__*) ; 
 scalar_t__ bfd_is_com_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_is_und_section (int /*<<< orphan*/ ) ; 

bfd_reloc_status_type
_bfd_mips_elf_got16_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
			   void *data, asection *input_section,
			   bfd *output_bfd, char **error_message)
{
  if ((symbol->flags & (BSF_GLOBAL | BSF_WEAK)) != 0
      || bfd_is_und_section (bfd_get_section (symbol))
      || bfd_is_com_section (bfd_get_section (symbol)))
    /* The relocation is against a global symbol.  */
    return _bfd_mips_elf_generic_reloc (abfd, reloc_entry, symbol, data,
					input_section, output_bfd,
					error_message);

  return _bfd_mips_elf_hi16_reloc (abfd, reloc_entry, symbol, data,
				   input_section, output_bfd, error_message);
}