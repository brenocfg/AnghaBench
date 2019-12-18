#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_14__ ;
typedef  struct TYPE_34__   TYPE_11__ ;

/* Type definitions */
struct TYPE_39__ {unsigned short value; TYPE_2__* section; } ;
struct TYPE_40__ {TYPE_3__ def; } ;
struct TYPE_41__ {scalar_t__ type; TYPE_4__ u; } ;
struct elf_link_hash_entry {TYPE_5__ root; } ;
struct bfd_link_info {int /*<<< orphan*/  keep_memory; scalar_t__ relocatable; } ;
typedef  unsigned short bfd_vma ;
struct TYPE_44__ {scalar_t__ st_shndx; unsigned short st_value; int r_offset; void* r_info; scalar_t__ r_addend; } ;
typedef  TYPE_8__ bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_45__ {int flags; scalar_t__ reloc_count; unsigned short output_offset; TYPE_6__* output_section; } ;
typedef  TYPE_9__ asection ;
struct TYPE_43__ {TYPE_8__* contents; } ;
struct TYPE_42__ {unsigned short vma; } ;
struct TYPE_38__ {unsigned short output_offset; TYPE_1__* output_section; } ;
struct TYPE_37__ {unsigned short vma; } ;
struct TYPE_36__ {TYPE_8__* relocs; TYPE_7__ this_hdr; } ;
struct TYPE_34__ {scalar_t__ sh_info; unsigned char* contents; } ;
struct TYPE_35__ {TYPE_11__ symtab_hdr; } ;
typedef  TYPE_8__ Elf_Internal_Sym ;
typedef  TYPE_11__ Elf_Internal_Shdr ;
typedef  TYPE_8__ Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 void* ELF32_R_INFO (int,scalar_t__) ; 
 int ELF32_R_SYM (void*) ; 
 int ELF32_R_TYPE (void*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ R_CR16_DISP16 ; 
 scalar_t__ R_CR16_DISP24 ; 
 scalar_t__ R_CR16_DISP8 ; 
 scalar_t__ R_CR16_IMM16 ; 
 scalar_t__ R_CR16_IMM20 ; 
 scalar_t__ R_CR16_IMM32 ; 
 scalar_t__ R_CR16_IMM4 ; 
 int SEC_CODE ; 
 int SEC_RELOC ; 
 scalar_t__ SHN_ABS ; 
 scalar_t__ SHN_COMMON ; 
 scalar_t__ SHN_UNDEF ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_8__* _bfd_elf_link_read_relocs (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_9__* bfd_abs_section_ptr ; 
 TYPE_9__* bfd_com_section_ptr ; 
 TYPE_8__* bfd_elf_get_elf_syms (int /*<<< orphan*/ *,TYPE_11__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_16 (int /*<<< orphan*/ *,TYPE_8__*) ; 
 scalar_t__ bfd_get_32 (int /*<<< orphan*/ *,TYPE_8__*) ; 
 scalar_t__ bfd_get_8 (int /*<<< orphan*/ *,TYPE_8__*) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 int /*<<< orphan*/  bfd_malloc_and_get_section (int /*<<< orphan*/ *,TYPE_9__*,TYPE_8__**) ; 
 int /*<<< orphan*/  bfd_put_16 (int /*<<< orphan*/ *,unsigned short,TYPE_8__*) ; 
 int /*<<< orphan*/  bfd_put_8 (int /*<<< orphan*/ *,unsigned short,TYPE_8__*) ; 
 TYPE_9__* bfd_section_from_elf_index (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_9__* bfd_und_section_ptr ; 
 int /*<<< orphan*/  elf32_cr16_relax_delete_bytes (struct bfd_link_info*,int /*<<< orphan*/ *,TYPE_9__*,int,int) ; 
 TYPE_15__* elf_section_data (TYPE_9__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_14__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_8__*) ; 

__attribute__((used)) static bfd_boolean
elf32_cr16_relax_section (bfd *abfd, asection *sec,
                         struct bfd_link_info *link_info, bfd_boolean *again)
{
  Elf_Internal_Shdr *symtab_hdr;
  Elf_Internal_Rela *internal_relocs;
  Elf_Internal_Rela *irel, *irelend;
  bfd_byte *contents = NULL;
  Elf_Internal_Sym *isymbuf = NULL;

  /* Assume nothing changes.  */
  *again = FALSE;

  /* We don't have to do anything for a relocatable link, if
     this section does not have relocs, or if this is not a
     code section.  */
  if (link_info->relocatable
      || (sec->flags & SEC_RELOC) == 0
      || sec->reloc_count == 0
      || (sec->flags & SEC_CODE) == 0)
    return TRUE;

  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;

  /* Get a copy of the native relocations.  */
  internal_relocs = _bfd_elf_link_read_relocs (abfd, sec, NULL, NULL,
					       link_info->keep_memory);
  if (internal_relocs == NULL)
    goto error_return;

  /* Walk through them looking for relaxing opportunities.  */
  irelend = internal_relocs + sec->reloc_count;
  for (irel = internal_relocs; irel < irelend; irel++)
    {
      bfd_vma symval;

      /* If this isn't something that can be relaxed, then ignore
         this reloc.  */
      if (ELF32_R_TYPE (irel->r_info) != (int) R_CR16_DISP16
          && ELF32_R_TYPE (irel->r_info) != (int) R_CR16_DISP24)
        continue;

      /* Get the section contents if we haven't done so already.  */
      if (contents == NULL)
        {
          /* Get cached copy if it exists.  */
          if (elf_section_data (sec)->this_hdr.contents != NULL)
            contents = elf_section_data (sec)->this_hdr.contents;
          /* Go get them off disk.  */
          else if (!bfd_malloc_and_get_section (abfd, sec, &contents))
            goto error_return;
        }

      /* Read this BFD's local symbols if we haven't done so already.  */
      if (isymbuf == NULL && symtab_hdr->sh_info != 0)
        {
          isymbuf = (Elf_Internal_Sym *) symtab_hdr->contents;
          if (isymbuf == NULL)
            isymbuf = bfd_elf_get_elf_syms (abfd, symtab_hdr,
                                            symtab_hdr->sh_info, 0,
                                            NULL, NULL, NULL);
          if (isymbuf == NULL)
            goto error_return;
        }

      /* Get the value of the symbol referred to by the reloc.  */
      if (ELF32_R_SYM (irel->r_info) < symtab_hdr->sh_info)
        {
          /* A local symbol.  */
          Elf_Internal_Sym *isym;
          asection *sym_sec;

          isym = isymbuf + ELF32_R_SYM (irel->r_info);
          if (isym->st_shndx == SHN_UNDEF)
            sym_sec = bfd_und_section_ptr;
          else if (isym->st_shndx == SHN_ABS)
            sym_sec = bfd_abs_section_ptr;
          else if (isym->st_shndx == SHN_COMMON)
            sym_sec = bfd_com_section_ptr;
          else
            sym_sec = bfd_section_from_elf_index (abfd, isym->st_shndx);
          symval = (isym->st_value
                    + sym_sec->output_section->vma
                    + sym_sec->output_offset);
        }
      else
        {
          unsigned long indx;
          struct elf_link_hash_entry *h;

          /* An external symbol.  */
          indx = ELF32_R_SYM (irel->r_info) - symtab_hdr->sh_info;
          h = elf_sym_hashes (abfd)[indx];
          BFD_ASSERT (h != NULL);

          if (h->root.type != bfd_link_hash_defined
              && h->root.type != bfd_link_hash_defweak)
            /* This appears to be a reference to an undefined
               symbol.  Just ignore it--it will be caught by the
               regular reloc processing.  */
            continue;

          symval = (h->root.u.def.value
                    + h->root.u.def.section->output_section->vma
                    + h->root.u.def.section->output_offset);
        }

      /* For simplicity of coding, we are going to modify the section
         contents, the section relocs, and the BFD symbol table.  We
         must tell the rest of the code not to free up this
         information.  It would be possible to instead create a table
         of changes which have to be made, as is done in coff-mips.c;
         that would be more work, but would require less memory when
         the linker is run.  */

      /* Try to turn a 24  branch/call into a 16bit relative
       * branch/call.  */
      if (ELF32_R_TYPE (irel->r_info) == (int) R_CR16_DISP24)
        {
          bfd_vma value = symval;

          /* Deal with pc-relative gunk.  */
          value -= (sec->output_section->vma + sec->output_offset);
          value -= irel->r_offset;
          value += irel->r_addend;

          /* See if the value will fit in 16 bits, note the high value is
             0xfffe + 2 as the target will be two bytes closer if we are
             able to relax.  */
          if ((long) value < 0x10000 && (long) value > -0x10002)
            {
              unsigned int code;

              /* Get the opcode.  */
              code = (unsigned int) bfd_get_32 (abfd, contents + irel->r_offset);

              /* Verify it's a 'bcond' and fix the opcode.  */
              if ((code  & 0xffff) == 0x0010)
                {
                bfd_put_16 (abfd, 0x1800 | ((0xf & (code >>20))<<4), contents + irel->r_offset);
                bfd_put_16 (abfd, value, contents + irel->r_offset+2);
                }
              else
                continue;

              /* Note that we've changed the relocs, section contents, etc.  */
              elf_section_data (sec)->relocs = internal_relocs;
              elf_section_data (sec)->this_hdr.contents = contents;
              symtab_hdr->contents = (unsigned char *) isymbuf;

              /* Fix the relocation's type.  */
              irel->r_info = ELF32_R_INFO (ELF32_R_SYM (irel->r_info),
                                           R_CR16_DISP16);

              /* Delete two bytes of data.  */
              if (!elf32_cr16_relax_delete_bytes (link_info, abfd, sec,
                                                   irel->r_offset + 2, 2))
                goto error_return;

              /* That will change things, so, we should relax again.
                 Note that this is not required, and it may be slow.  */
              *again = TRUE;
            }
        }

      /* Try to turn a 16bit pc-relative branch into an
         8bit pc-relative branch.  */
      if (ELF32_R_TYPE (irel->r_info) == (int) R_CR16_DISP16)
        {
          bfd_vma value = symval;

          /* Deal with pc-relative gunk.  */
          value -= (sec->output_section->vma + sec->output_offset);
          value -= irel->r_offset;
          value += irel->r_addend;

          /* See if the value will fit in 8 bits, note the high value is
             0xfc + 2 as the target will be two bytes closer if we are
             able to relax.  */
          if ((long) value < 0xfe && (long) value > -0x100)
            {
              unsigned short code;

              /* Get the opcode.  */
              code = (unsigned short) bfd_get_16 (abfd, contents + irel->r_offset);

              /* Verify it's a 'bcond' opcode.  */
              if ((code & 0xff00) == 0x1800)
                {
                 bfd_put_8 (abfd, 0x1 | ((0xf & (code>>4))<<4), contents + irel->r_offset);
                 bfd_put_8 (abfd, value, contents + irel->r_offset+2);
                }
              else
                continue;

              /* Note that we've changed the relocs, section contents, etc.  */
              elf_section_data (sec)->relocs = internal_relocs;
              elf_section_data (sec)->this_hdr.contents = contents;
              symtab_hdr->contents = (unsigned char *) isymbuf;

              /* Fix the relocation's type.  */
              irel->r_info = ELF32_R_INFO (ELF32_R_SYM (irel->r_info),
                                           R_CR16_DISP8);

              /* Delete two bytes of data.  */
              if (!elf32_cr16_relax_delete_bytes (link_info, abfd, sec,
                                                   irel->r_offset + 2, 2))
                goto error_return;

              /* That will change things, so, we should relax again.
                 Note that this is not required, and it may be slow.  */
              *again = TRUE;
            }
        }

#if 0 // REVISIT: To support IMM relaxation in CR16 target
      /* Try to turn a 32bit immediate address into
         a 20bit immediate address.  */
      if (ELF32_R_TYPE (irel->r_info) == (int) R_CR16_IMM32)
        {
          bfd_vma value = symval;

          /* See if the value will fit in 20 bits.  */
          if ((long) value < 0x7ffff && (long) value > -0x80000)
            {
              unsigned short code;

              /* Get the opcode.  */
              code = (unsigned short) bfd_get_16 (abfd, contents + irel->r_offset);

              /* Verify it's a 'arithmetic double'.  */
              if ((code & 0xfff0) != 0x0070)
                continue;

              /* Note that we've changed the relocs, section contents, etc.  */
              elf_section_data (sec)->relocs = internal_relocs;
              elf_section_data (sec)->this_hdr.contents = contents;
              symtab_hdr->contents = (unsigned char *) isymbuf;

              /* Fix the opcode.  */
              bfd_put_8 (abfd, (code & 0xff) - 0x10, contents + irel->r_offset);

              /* Fix the relocation's type.  */
              irel->r_info = ELF32_R_INFO (ELF32_R_SYM (irel->r_info),
                                           R_CR16_IMM20);

              /* Delete two bytes of data.  */
              if (!elf32_cr16_relax_delete_bytes (link_info, abfd, sec,
                                                   irel->r_offset + 2, 2))
                goto error_return;

              /* That will change things, so, we should relax again.
                 Note that this is not required, and it may be slow.  */
              *again = TRUE;
            }
        }
      /* Try to turn a 20bit/16bit immediate address into
         a 4bit immediate address.  */
      if ((ELF32_R_TYPE (irel->r_info) == (int) R_CR16_IMM20)
	  || (ELF32_R_TYPE (irel->r_info) == (int) R_CR16_IMM16))
        {
          bfd_vma value = symval;

          /* See if the value will fit in 4 bits.  */
          if ((long) value < 0x7 && (long) value > -0x8)
            {
              unsigned short code;

              /* Get the opcode.  */
              code = (unsigned short) bfd_get_8 (abfd, contents + irel->r_offset);

              /* Verify it's a 'arithmetic double'.  */
              if (((code & 0xff) != 0x50) || ((code & 0xff) != 0x45))
                continue;

              /* Note that we've changed the relocs, section contents, etc.  */
              elf_section_data (sec)->relocs = internal_relocs;
              elf_section_data (sec)->this_hdr.contents = contents;
              symtab_hdr->contents = (unsigned char *) isymbuf;

              /* Fix the opcode.  */
              bfd_put_8 (abfd, (code & 0xff) - 0x10, contents + irel->r_offset);

              /* Fix the relocation's type.  */
              irel->r_info = ELF32_R_INFO (ELF32_R_SYM (irel->r_info),
                                           R_CR16_IMM4);

              /* Delete two bytes of data.  */
              if (!elf32_cr16_relax_delete_bytes (link_info, abfd, sec,
                                                   irel->r_offset + 2, 2))
                goto error_return;

              /* That will change things, so, we should relax again.
                 Note that this is not required, and it may be slow.  */
              *again = TRUE;
            }
        }
#endif
    }

  if (isymbuf != NULL
      && symtab_hdr->contents != (unsigned char *) isymbuf)
    {
      if (! link_info->keep_memory)
        free (isymbuf);
      else
        {
          /* Cache the symbols for elf_link_input_bfd.  */
          symtab_hdr->contents = (unsigned char *) isymbuf;
        }
    }

  if (contents != NULL
      && elf_section_data (sec)->this_hdr.contents != contents)
    {
      if (! link_info->keep_memory)
        free (contents);
      else
        {
          /* Cache the section contents for elf_link_input_bfd.  */
          elf_section_data (sec)->this_hdr.contents = contents;
        }
    }

  if (internal_relocs != NULL
      && elf_section_data (sec)->relocs != internal_relocs)
    free (internal_relocs);

  return TRUE;

 error_return:
  if (isymbuf != NULL
      && symtab_hdr->contents != (unsigned char *) isymbuf)
    free (isymbuf);
  if (contents != NULL
      && elf_section_data (sec)->this_hdr.contents != contents)
    free (contents);
  if (internal_relocs != NULL
      && elf_section_data (sec)->relocs != internal_relocs)
    free (internal_relocs);

  return FALSE;
}