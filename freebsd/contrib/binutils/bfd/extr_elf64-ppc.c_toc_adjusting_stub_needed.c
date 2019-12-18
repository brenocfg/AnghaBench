#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_24__ ;
typedef  struct TYPE_33__   TYPE_23__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_13__ ;
typedef  struct TYPE_30__   TYPE_12__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
struct ppc_link_hash_table {size_t top_id; TYPE_10__* stub_group; } ;
struct TYPE_32__ {int /*<<< orphan*/ * plist; } ;
struct TYPE_35__ {TYPE_1__ plt; } ;
struct ppc_link_hash_entry {TYPE_5__* oh; TYPE_2__ elf; } ;
struct TYPE_39__ {scalar_t__ value; } ;
struct TYPE_40__ {TYPE_6__ def; } ;
struct TYPE_41__ {scalar_t__ type; TYPE_7__ u; } ;
struct elf_link_hash_entry {TYPE_8__ root; } ;
struct bfd_link_info {int /*<<< orphan*/  keep_memory; } ;
typedef  enum elf_ppc64_reloc_type { ____Placeholder_elf_ppc64_reloc_type } elf_ppc64_reloc_type ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_30__ {int flags; scalar_t__ size; scalar_t__ reloc_count; scalar_t__ output_offset; int makes_toc_func_call; int call_check_in_progress; size_t id; int /*<<< orphan*/  owner; TYPE_9__* output_section; scalar_t__ has_toc_reloc; int /*<<< orphan*/  name; } ;
typedef  TYPE_12__ asection ;
struct TYPE_42__ {scalar_t__ vma; } ;
struct TYPE_36__ {int /*<<< orphan*/ * plist; } ;
struct TYPE_37__ {TYPE_3__ plt; } ;
struct TYPE_38__ {TYPE_4__ elf; } ;
struct TYPE_34__ {TYPE_13__* relocs; } ;
struct TYPE_29__ {unsigned char* contents; } ;
struct TYPE_33__ {TYPE_11__ symtab_hdr; } ;
struct TYPE_31__ {scalar_t__ st_value; scalar_t__ r_addend; scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_28__ {int toc_off; } ;
typedef  TYPE_13__ Elf_Internal_Sym ;
typedef  TYPE_13__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned long ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int R_PPC64_REL14 ; 
 int R_PPC64_REL14_BRNTAKEN ; 
 int R_PPC64_REL14_BRTAKEN ; 
 int R_PPC64_REL24 ; 
 int SEC_LINKER_CREATED ; 
 TYPE_13__* _bfd_elf_link_read_relocs (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 TYPE_24__* elf_section_data (TYPE_12__*) ; 
 TYPE_23__* elf_tdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_13__*) ; 
 long* get_opd_info (TYPE_12__*) ; 
 int /*<<< orphan*/  get_sym_h (struct elf_link_hash_entry**,TYPE_13__**,TYPE_12__**,int /*<<< orphan*/ *,TYPE_13__**,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ opd_entry_value (TYPE_12__*,scalar_t__,TYPE_12__**,int /*<<< orphan*/ *) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
toc_adjusting_stub_needed (struct bfd_link_info *info, asection *isec)
{
  Elf_Internal_Rela *relstart, *rel;
  Elf_Internal_Sym *local_syms;
  int ret;
  struct ppc_link_hash_table *htab;

  /* We know none of our code bearing sections will need toc stubs.  */
  if ((isec->flags & SEC_LINKER_CREATED) != 0)
    return 0;

  if (isec->size == 0)
    return 0;

  if (isec->output_section == NULL)
    return 0;

  /* Hack for linux kernel.  .fixup contains branches, but only back to
     the function that hit an exception.  */
  if (strcmp (isec->name, ".fixup") == 0)
    return 0;

  if (isec->reloc_count == 0)
    return 0;

  relstart = _bfd_elf_link_read_relocs (isec->owner, isec, NULL, NULL,
					info->keep_memory);
  if (relstart == NULL)
    return -1;

  /* Look for branches to outside of this section.  */
  local_syms = NULL;
  ret = 0;
  htab = ppc_hash_table (info);
  for (rel = relstart; rel < relstart + isec->reloc_count; ++rel)
    {
      enum elf_ppc64_reloc_type r_type;
      unsigned long r_symndx;
      struct elf_link_hash_entry *h;
      struct ppc_link_hash_entry *eh;
      Elf_Internal_Sym *sym;
      asection *sym_sec;
      long *opd_adjust;
      bfd_vma sym_value;
      bfd_vma dest;

      r_type = ELF64_R_TYPE (rel->r_info);
      if (r_type != R_PPC64_REL24
	  && r_type != R_PPC64_REL14
	  && r_type != R_PPC64_REL14_BRTAKEN
	  && r_type != R_PPC64_REL14_BRNTAKEN)
	continue;

      r_symndx = ELF64_R_SYM (rel->r_info);
      if (!get_sym_h (&h, &sym, &sym_sec, NULL, &local_syms, r_symndx,
		      isec->owner))
	{
	  ret = -1;
	  break;
	}

      /* Calls to dynamic lib functions go through a plt call stub
	 that uses r2.  */
      eh = (struct ppc_link_hash_entry *) h;
      if (eh != NULL
	  && (eh->elf.plt.plist != NULL
	      || (eh->oh != NULL
		  && eh->oh->elf.plt.plist != NULL)))
	{
	  ret = 1;
	  break;
	}

      if (sym_sec == NULL)
	/* Ignore other undefined symbols.  */
	continue;

      /* Assume branches to other sections not included in the link need
	 stubs too, to cover -R and absolute syms.  */
      if (sym_sec->output_section == NULL)
	{
	  ret = 1;
	  break;
	}

      if (h == NULL)
	sym_value = sym->st_value;
      else
	{
	  if (h->root.type != bfd_link_hash_defined
	      && h->root.type != bfd_link_hash_defweak)
	    abort ();
	  sym_value = h->root.u.def.value;
	}
      sym_value += rel->r_addend;

      /* If this branch reloc uses an opd sym, find the code section.  */
      opd_adjust = get_opd_info (sym_sec);
      if (opd_adjust != NULL)
	{
	  if (h == NULL)
	    {
	      long adjust;

	      adjust = opd_adjust[sym->st_value / 8];
	      if (adjust == -1)
		/* Assume deleted functions won't ever be called.  */
		continue;
	      sym_value += adjust;
	    }

	  dest = opd_entry_value (sym_sec, sym_value, &sym_sec, NULL);
	  if (dest == (bfd_vma) -1)
	    continue;
	}
      else
	dest = (sym_value
		+ sym_sec->output_offset
		+ sym_sec->output_section->vma);

      /* Ignore branch to self.  */
      if (sym_sec == isec)
	continue;

      /* If the called function uses the toc, we need a stub.  */
      if (sym_sec->has_toc_reloc
	  || sym_sec->makes_toc_func_call)
	{
	  ret = 1;
	  break;
	}

      /* Assume any branch that needs a long branch stub might in fact
	 need a plt_branch stub.  A plt_branch stub uses r2.  */
      else if (dest - (isec->output_offset
		       + isec->output_section->vma
		       + rel->r_offset) + (1 << 25) >= (2 << 25))
	{
	  ret = 1;
	  break;
	}

      /* If calling back to a section in the process of being tested, we
	 can't say for sure that no toc adjusting stubs are needed, so
	 don't return zero.  */
      else if (sym_sec->call_check_in_progress)
	ret = 2;

      /* Branches to another section that itself doesn't have any TOC
	 references are OK.  Recursively call ourselves to check.  */
      else if (sym_sec->id <= htab->top_id
	       && htab->stub_group[sym_sec->id].toc_off == 0)
	{
	  int recur;

	  /* Mark current section as indeterminate, so that other
	     sections that call back to current won't be marked as
	     known.  */
	  isec->call_check_in_progress = 1;
	  recur = toc_adjusting_stub_needed (info, sym_sec);
	  isec->call_check_in_progress = 0;

	  if (recur < 0)
	    {
	      /* An error.  Exit.  */
	      ret = -1;
	      break;
	    }
	  else if (recur <= 1)
	    {
	      /* Known result.  Mark as checked and set section flag.  */
	      htab->stub_group[sym_sec->id].toc_off = 1;
	      if (recur != 0)
		{
		  sym_sec->makes_toc_func_call = 1;
		  ret = 1;
		  break;
		}
	    }
	  else
	    {
	      /* Unknown result.  Continue checking.  */
	      ret = 2;
	    }
	}
    }

  if (local_syms != NULL
      && (elf_tdata (isec->owner)->symtab_hdr.contents
	  != (unsigned char *) local_syms))
    free (local_syms);
  if (elf_section_data (isec)->relocs != relstart)
    free (relstart);

  return ret;
}