#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_21__ {int flags; scalar_t__ xvec; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_22__ {scalar_t__ value; int /*<<< orphan*/  section; TYPE_1__* the_bfd; } ;
typedef  TYPE_4__ asymbol ;
struct TYPE_23__ {unsigned int reloc_count; scalar_t__ vma; TYPE_6__** orelocation; } ;
typedef  TYPE_5__ asection ;
struct TYPE_24__ {scalar_t__ address; TYPE_2__* howto; TYPE_4__** sym_ptr_ptr; int /*<<< orphan*/  addend; } ;
typedef  TYPE_6__ arelent ;
struct TYPE_26__ {scalar_t__ r_offset; int r_sym; int r_type; int r_type2; int r_type3; int /*<<< orphan*/  r_ssym; int /*<<< orphan*/  r_addend; } ;
struct TYPE_25__ {int sh_size; int sh_entsize; int /*<<< orphan*/ * contents; } ;
struct TYPE_20__ {int type; } ;
struct TYPE_19__ {scalar_t__ xvec; } ;
typedef  TYPE_7__ Elf_Internal_Shdr ;
typedef  TYPE_8__ Elf64_Mips_Internal_Rela ;
typedef  int /*<<< orphan*/  Elf64_Mips_External_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int DYNAMIC ; 
 int EXEC_P ; 
 int /*<<< orphan*/  RSS_UNDEF ; 
 scalar_t__ R_MIPS_NONE ; 
 int STN_UNDEF ; 
 int /*<<< orphan*/  TRUE ; 
 int _bfd_elf_symbol_from_bfd_symbol (TYPE_3__*,TYPE_4__**) ; 
 int /*<<< orphan*/  _bfd_elf_validate_reloc (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/ * bfd_alloc (TYPE_3__*,int) ; 
 scalar_t__ bfd_is_abs_section (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_elf64_swap_reloca_out (TYPE_3__*,TYPE_8__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mips_elf64_write_rela (bfd *abfd, asection *sec,
		       Elf_Internal_Shdr *rela_hdr,
		       int *count, void *data)
{
  bfd_boolean *failedp = data;
  Elf64_Mips_External_Rela *ext_rela;
  unsigned int idx;
  asymbol *last_sym = 0;
  int last_sym_idx = 0;

  rela_hdr->sh_size = rela_hdr->sh_entsize * *count;
  rela_hdr->contents = bfd_alloc (abfd, rela_hdr->sh_size);
  if (rela_hdr->contents == NULL)
    {
      *failedp = TRUE;
      return;
    }

  ext_rela = (Elf64_Mips_External_Rela *) rela_hdr->contents;
  for (idx = 0; idx < sec->reloc_count; idx++, ext_rela++)
    {
      arelent *ptr;
      Elf64_Mips_Internal_Rela int_rela;
      asymbol *sym;
      int n;
      unsigned int i;

      ptr = sec->orelocation[idx];

      /* The address of an ELF reloc is section relative for an object
	 file, and absolute for an executable file or shared library.
	 The address of a BFD reloc is always section relative.  */
      if ((abfd->flags & (EXEC_P | DYNAMIC)) == 0)
	int_rela.r_offset = ptr->address;
      else
	int_rela.r_offset = ptr->address + sec->vma;

      sym = *ptr->sym_ptr_ptr;
      if (sym == last_sym)
	n = last_sym_idx;
      else if (bfd_is_abs_section (sym->section) && sym->value == 0)
	n = STN_UNDEF;
      else
	{
	  last_sym = sym;
	  n = _bfd_elf_symbol_from_bfd_symbol (abfd, &sym);
	  if (n < 0)
	    {
	      *failedp = TRUE;
	      return;
	    }
	  last_sym_idx = n;
	}

      int_rela.r_sym = n;
      int_rela.r_addend = ptr->addend;
      int_rela.r_ssym = RSS_UNDEF;

      if ((*ptr->sym_ptr_ptr)->the_bfd->xvec != abfd->xvec
	  && ! _bfd_elf_validate_reloc (abfd, ptr))
	{
	  *failedp = TRUE;
	  return;
	}

      int_rela.r_type = ptr->howto->type;
      int_rela.r_type2 = (int) R_MIPS_NONE;
      int_rela.r_type3 = (int) R_MIPS_NONE;

      for (i = 0; i < 2; i++)
	{
	  arelent *r;

	  if (idx + 1 >= sec->reloc_count)
	    break;
	  r = sec->orelocation[idx + 1];
	  if (r->address != ptr->address
	      || ! bfd_is_abs_section ((*r->sym_ptr_ptr)->section)
	      || (*r->sym_ptr_ptr)->value != 0)
	    break;

	  /* We can merge the reloc at IDX + 1 with the reloc at IDX.  */

	  if (i == 0)
	    int_rela.r_type2 = r->howto->type;
	  else
	    int_rela.r_type3 = r->howto->type;

	  ++idx;
	}

      mips_elf64_swap_reloca_out (abfd, &int_rela, ext_rela);
    }

  BFD_ASSERT (ext_rela - (Elf64_Mips_External_Rela *) rela_hdr->contents
	      == *count);
}