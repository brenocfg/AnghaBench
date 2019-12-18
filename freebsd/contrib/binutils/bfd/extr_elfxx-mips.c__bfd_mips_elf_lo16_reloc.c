#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int address; int addend; TYPE_4__* howto; } ;
struct mips_hi16 {void* data; struct mips_hi16* next; int /*<<< orphan*/ * input_section; TYPE_1__ rel; } ;
typedef  int bfd_vma ;
typedef  scalar_t__ bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;
typedef  TYPE_1__ arelent ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_4__* MIPS_ELF_RTYPE_TO_HOWTO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ R_MIPS_GOT16 ; 
 int /*<<< orphan*/  R_MIPS_HI16 ; 
 int /*<<< orphan*/  _bfd_mips16_elf_reloc_shuffle (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_mips16_elf_reloc_unshuffle (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _bfd_mips_elf_generic_reloc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_reloc_ok ; 
 scalar_t__ bfd_reloc_outofrange ; 
 int /*<<< orphan*/  free (struct mips_hi16*) ; 
 struct mips_hi16* mips_hi16_list ; 

bfd_reloc_status_type
_bfd_mips_elf_lo16_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
			  void *data, asection *input_section,
			  bfd *output_bfd, char **error_message)
{
  bfd_vma vallo;
  bfd_byte *location = (bfd_byte *) data + reloc_entry->address;

  if (reloc_entry->address > bfd_get_section_limit (abfd, input_section))
    return bfd_reloc_outofrange;

  _bfd_mips16_elf_reloc_unshuffle (abfd, reloc_entry->howto->type, FALSE,
				   location);
  vallo = bfd_get_32 (abfd, location);
  _bfd_mips16_elf_reloc_shuffle (abfd, reloc_entry->howto->type, FALSE,
				 location);

  while (mips_hi16_list != NULL)
    {
      bfd_reloc_status_type ret;
      struct mips_hi16 *hi;

      hi = mips_hi16_list;

      /* R_MIPS_GOT16 relocations are something of a special case.  We
	 want to install the addend in the same way as for a R_MIPS_HI16
	 relocation (with a rightshift of 16).  However, since GOT16
	 relocations can also be used with global symbols, their howto
	 has a rightshift of 0.  */
      if (hi->rel.howto->type == R_MIPS_GOT16)
	hi->rel.howto = MIPS_ELF_RTYPE_TO_HOWTO (abfd, R_MIPS_HI16, FALSE);

      /* VALLO is a signed 16-bit number.  Bias it by 0x8000 so that any
	 carry or borrow will induce a change of +1 or -1 in the high part.  */
      hi->rel.addend += (vallo + 0x8000) & 0xffff;

      ret = _bfd_mips_elf_generic_reloc (abfd, &hi->rel, symbol, hi->data,
					 hi->input_section, output_bfd,
					 error_message);
      if (ret != bfd_reloc_ok)
	return ret;

      mips_hi16_list = hi->next;
      free (hi);
    }

  return _bfd_mips_elf_generic_reloc (abfd, reloc_entry, symbol, data,
				      input_section, output_bfd,
				      error_message);
}