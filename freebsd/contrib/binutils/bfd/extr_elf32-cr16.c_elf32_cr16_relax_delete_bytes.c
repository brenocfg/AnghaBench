#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int value; TYPE_5__* section; } ;
struct TYPE_17__ {TYPE_2__ def; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_3__ u; } ;
struct elf_link_hash_entry {TYPE_4__ root; } ;
struct bfd_link_info {int /*<<< orphan*/ * wrap_hash; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_19__ {int size; int reloc_count; } ;
typedef  TYPE_5__ asection ;
struct TYPE_21__ {int sh_info; int sh_size; scalar_t__ contents; } ;
struct TYPE_23__ {TYPE_7__ symtab_hdr; } ;
struct TYPE_22__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_20__ {unsigned int st_shndx; int st_value; } ;
struct TYPE_15__ {int /*<<< orphan*/ * contents; } ;
struct TYPE_14__ {TYPE_8__* relocs; TYPE_1__ this_hdr; } ;
typedef  TYPE_6__ Elf_Internal_Sym ;
typedef  TYPE_7__ Elf_Internal_Shdr ;
typedef  TYPE_8__ Elf_Internal_Rela ;
typedef  int /*<<< orphan*/  Elf32_External_Sym ;

/* Variables and functions */
 unsigned long ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int _bfd_elf_section_from_bfd_section (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 TYPE_10__* elf_section_data (TYPE_5__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_9__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static bfd_boolean
elf32_cr16_relax_delete_bytes (struct bfd_link_info *link_info, bfd *abfd,
                               asection *sec, bfd_vma addr, int count)
{
  Elf_Internal_Shdr *symtab_hdr;
  unsigned int sec_shndx;
  bfd_byte *contents;
  Elf_Internal_Rela *irel, *irelend;
  Elf_Internal_Rela *irelalign;
  bfd_vma toaddr;
  Elf_Internal_Sym *isym;
  Elf_Internal_Sym *isymend;
  struct elf_link_hash_entry **sym_hashes;
  struct elf_link_hash_entry **end_hashes;
  struct elf_link_hash_entry **start_hashes;
  unsigned int symcount;

  sec_shndx = _bfd_elf_section_from_bfd_section (abfd, sec);

  contents = elf_section_data (sec)->this_hdr.contents;

  /* The deletion must stop at the next ALIGN reloc for an aligment
     power larger than the number of bytes we are deleting.  */
  irelalign = NULL;
  toaddr = sec->size;

  irel = elf_section_data (sec)->relocs;
  irelend = irel + sec->reloc_count;

  /* Actually delete the bytes.  */
  memmove (contents + addr, contents + addr + count,
           (size_t) (toaddr - addr - count));
  sec->size -= count;

  /* Adjust all the relocs.  */
  for (irel = elf_section_data (sec)->relocs; irel < irelend; irel++)
    /* Get the new reloc address.  */
    if ((irel->r_offset > addr && irel->r_offset < toaddr))
	irel->r_offset -= count;

  /* Adjust the local symbols defined in this section.  */
  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  isym = (Elf_Internal_Sym *) symtab_hdr->contents;
  for (isymend = isym + symtab_hdr->sh_info; isym < isymend; isym++)
    {
      if (isym->st_shndx == sec_shndx
          && isym->st_value > addr
          && isym->st_value < toaddr)
        {
          /* Adjust the addend of SWITCH relocations in this section,
             which reference this local symbol.  */
          for (irel = elf_section_data (sec)->relocs; irel < irelend; irel++)
            {
              unsigned long r_symndx;
              Elf_Internal_Sym *rsym;
              bfd_vma addsym, subsym;

              r_symndx = ELF32_R_SYM (irel->r_info);
              rsym = (Elf_Internal_Sym *) symtab_hdr->contents + r_symndx;

              /* Skip if not the local adjusted symbol.  */
              if (rsym != isym)
                continue;

              addsym = isym->st_value;
              subsym = addsym - irel->r_addend;

              /* Fix the addend only when -->> (addsym > addr >= subsym).  */
              if (subsym <= addr)
                irel->r_addend -= count;
              else
                continue;
            }

          isym->st_value -= count;
        }
    }

  /* Now adjust the global symbols defined in this section.  */
  symcount = (symtab_hdr->sh_size / sizeof (Elf32_External_Sym)
               - symtab_hdr->sh_info);
  sym_hashes = start_hashes = elf_sym_hashes (abfd);
  end_hashes = sym_hashes + symcount;

  for (; sym_hashes < end_hashes; sym_hashes++)
    {
      struct elf_link_hash_entry *sym_hash = *sym_hashes;

      /* The '--wrap SYMBOL' option is causing a pain when the object file,
         containing the definition of __wrap_SYMBOL, includes a direct
         call to SYMBOL as well. Since both __wrap_SYMBOL and SYMBOL reference
         the same symbol (which is __wrap_SYMBOL), but still exist as two
         different symbols in 'sym_hashes', we don't want to adjust
         the global symbol __wrap_SYMBOL twice.
         This check is only relevant when symbols are being wrapped.  */
      if (link_info->wrap_hash != NULL)
        {
          struct elf_link_hash_entry **cur_sym_hashes;

          /* Loop only over the symbols whom been already checked.  */
          for (cur_sym_hashes = start_hashes; cur_sym_hashes < sym_hashes;
               cur_sym_hashes++)
	    /* If the current symbol is identical to 'sym_hash', that means
	       the symbol was already adjusted (or at least checked).  */
	    if (*cur_sym_hashes == sym_hash)
	      break;

          /* Don't adjust the symbol again.  */
          if (cur_sym_hashes < sym_hashes)
            continue;
        }

      if ((sym_hash->root.type == bfd_link_hash_defined
          || sym_hash->root.type == bfd_link_hash_defweak)
          && sym_hash->root.u.def.section == sec
          && sym_hash->root.u.def.value > addr
          && sym_hash->root.u.def.value < toaddr)
        sym_hash->root.u.def.value -= count;
    }

  return TRUE;
}