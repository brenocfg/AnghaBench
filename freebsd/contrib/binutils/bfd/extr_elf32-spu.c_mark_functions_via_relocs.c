#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_17__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {struct elf_link_hash_entry* sym; } ;
struct function_info {TYPE_6__ u; } ;
struct TYPE_26__ {int /*<<< orphan*/  value; } ;
struct TYPE_27__ {TYPE_3__ def; } ;
struct TYPE_28__ {TYPE_4__ u; } ;
struct elf_link_hash_entry {int is_tail; TYPE_7__* fun; int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_value; TYPE_5__ root; } ;
struct call_info {int is_tail; TYPE_7__* fun; int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_value; TYPE_5__ root; } ;
struct bfd_link_info {TYPE_2__* callbacks; int /*<<< orphan*/  keep_memory; } ;
typedef  enum elf_spu_reloc_type { ____Placeholder_elf_spu_reloc_type } elf_spu_reloc_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_31__ {scalar_t__ owner; int reloc_count; int flags; TYPE_1__* output_section; } ;
typedef  TYPE_8__ asection ;
struct TYPE_32__ {int /*<<< orphan*/  contents; } ;
struct TYPE_30__ {int is_func; scalar_t__ stack; struct function_info* start; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* einfo ) (int /*<<< orphan*/ ,scalar_t__,TYPE_8__*,int /*<<< orphan*/ ,scalar_t__,TYPE_8__*) ;} ;
struct TYPE_24__ {scalar_t__ owner; } ;
struct TYPE_23__ {TYPE_9__ symtab_hdr; } ;
struct TYPE_22__ {scalar_t__ r_addend; int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_info; } ;
typedef  struct elf_link_hash_entry Elf_Internal_Sym ;
typedef  TYPE_9__ Elf_Internal_Shdr ;
typedef  TYPE_10__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int R_SPU_ADDR16 ; 
 int R_SPU_REL16 ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_LOAD ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_10__* _bfd_elf_link_read_relocs (scalar_t__,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bfd_elf_section_from_bfd_section (scalar_t__,TYPE_8__*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (scalar_t__,TYPE_8__*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct elf_link_hash_entry* bfd_malloc (int) ; 
 struct elf_link_hash_entry* bfd_zmalloc (int) ; 
 TYPE_17__* elf_tdata (scalar_t__) ; 
 void* find_function (TYPE_8__*,int /*<<< orphan*/ ,struct bfd_link_info*) ; 
 int /*<<< orphan*/  free (struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  get_sym_h (struct elf_link_hash_entry**,struct elf_link_hash_entry**,TYPE_8__**,void*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  insert_callee (struct function_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  is_branch (unsigned char*) ; 
 struct function_info* maybe_insert_function (TYPE_8__*,struct elf_link_hash_entry*,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,TYPE_8__*,int /*<<< orphan*/ ,scalar_t__,TYPE_8__*) ; 

__attribute__((used)) static bfd_boolean
mark_functions_via_relocs (asection *sec,
			   struct bfd_link_info *info,
			   int call_tree)
{
  Elf_Internal_Rela *internal_relocs, *irelaend, *irela;
  Elf_Internal_Shdr *symtab_hdr = &elf_tdata (sec->owner)->symtab_hdr;
  Elf_Internal_Sym *syms;
  void *psyms;
  static bfd_boolean warned;

  internal_relocs = _bfd_elf_link_read_relocs (sec->owner, sec, NULL, NULL,
					       info->keep_memory);
  if (internal_relocs == NULL)
    return FALSE;

  symtab_hdr = &elf_tdata (sec->owner)->symtab_hdr;
  psyms = &symtab_hdr->contents;
  syms = *(Elf_Internal_Sym **) psyms;
  irela = internal_relocs;
  irelaend = irela + sec->reloc_count;
  for (; irela < irelaend; irela++)
    {
      enum elf_spu_reloc_type r_type;
      unsigned int r_indx;
      asection *sym_sec;
      Elf_Internal_Sym *sym;
      struct elf_link_hash_entry *h;
      bfd_vma val;
      unsigned char insn[4];
      bfd_boolean is_call;
      struct function_info *caller;
      struct call_info *callee;

      r_type = ELF32_R_TYPE (irela->r_info);
      if (r_type != R_SPU_REL16
	  && r_type != R_SPU_ADDR16)
	continue;

      r_indx = ELF32_R_SYM (irela->r_info);
      if (!get_sym_h (&h, &sym, &sym_sec, psyms, r_indx, sec->owner))
	return FALSE;

      if (sym_sec == NULL
	  || sym_sec->output_section == NULL
	  || sym_sec->output_section->owner != sec->output_section->owner)
	continue;

      if (!bfd_get_section_contents (sec->owner, sec, insn,
				     irela->r_offset, 4))
	return FALSE;
      if (!is_branch (insn))
	continue;

      if ((sym_sec->flags & (SEC_ALLOC | SEC_LOAD | SEC_CODE))
	  != (SEC_ALLOC | SEC_LOAD | SEC_CODE))
	{
	  if (!call_tree)
	    warned = TRUE;
	  if (!call_tree || !warned)
	    info->callbacks->einfo (_("%B(%A+0x%v): call to non-code section"
				      " %B(%A), stack analysis incomplete\n"),
				    sec->owner, sec, irela->r_offset,
				    sym_sec->owner, sym_sec);
	  continue;
	}

      is_call = (insn[0] & 0xfd) == 0x31;

      if (h)
	val = h->root.u.def.value;
      else
	val = sym->st_value;
      val += irela->r_addend;

      if (!call_tree)
	{
	  struct function_info *fun;

	  if (irela->r_addend != 0)
	    {
	      Elf_Internal_Sym *fake = bfd_zmalloc (sizeof (*fake));
	      if (fake == NULL)
		return FALSE;
	      fake->st_value = val;
	      fake->st_shndx
		= _bfd_elf_section_from_bfd_section (sym_sec->owner, sym_sec);
	      sym = fake;
	    }
	  if (sym)
	    fun = maybe_insert_function (sym_sec, sym, FALSE, is_call);
	  else
	    fun = maybe_insert_function (sym_sec, h, TRUE, is_call);
	  if (fun == NULL)
	    return FALSE;
	  if (irela->r_addend != 0
	      && fun->u.sym != sym)
	    free (sym);
	  continue;
	}

      caller = find_function (sec, irela->r_offset, info);
      if (caller == NULL)
	return FALSE;
      callee = bfd_malloc (sizeof *callee);
      if (callee == NULL)
	return FALSE;

      callee->fun = find_function (sym_sec, val, info);
      if (callee->fun == NULL)
	return FALSE;
      callee->is_tail = !is_call;
      if (!insert_callee (caller, callee))
	free (callee);
      else if (!is_call
	       && !callee->fun->is_func
	       && callee->fun->stack == 0)
	{
	  /* This is either a tail call or a branch from one part of
	     the function to another, ie. hot/cold section.  If the
	     destination has been called by some other function then
	     it is a separate function.  We also assume that functions
	     are not split across input files.  */
	  if (callee->fun->start != NULL
	      || sec->owner != sym_sec->owner)
	    {
	      callee->fun->start = NULL;
	      callee->fun->is_func = TRUE;
	    }
	  else
	    callee->fun->start = caller;
	}
    }

  return TRUE;
}