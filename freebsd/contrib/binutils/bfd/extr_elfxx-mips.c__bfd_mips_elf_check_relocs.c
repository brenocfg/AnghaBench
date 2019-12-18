#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_75__   TYPE_9__ ;
typedef  struct TYPE_74__   TYPE_8__ ;
typedef  struct TYPE_73__   TYPE_7__ ;
typedef  struct TYPE_72__   TYPE_6__ ;
typedef  struct TYPE_71__   TYPE_5__ ;
typedef  struct TYPE_70__   TYPE_4__ ;
typedef  struct TYPE_69__   TYPE_3__ ;
typedef  struct TYPE_68__   TYPE_37__ ;
typedef  struct TYPE_67__   TYPE_35__ ;
typedef  struct TYPE_66__   TYPE_32__ ;
typedef  struct TYPE_65__   TYPE_2__ ;
typedef  struct TYPE_64__   TYPE_1__ ;
typedef  struct TYPE_63__   TYPE_17__ ;
typedef  struct TYPE_62__   TYPE_13__ ;
typedef  struct TYPE_61__   TYPE_12__ ;
typedef  struct TYPE_60__   TYPE_11__ ;
typedef  struct TYPE_59__   TYPE_10__ ;

/* Type definitions */
struct mips_got_info {int dummy; } ;
struct mips_elf_link_hash_table {int compact_rel_size; scalar_t__ is_vxworks; void* mips16_stubs_seen; } ;
struct TYPE_72__ {scalar_t__ link; } ;
struct TYPE_73__ {TYPE_6__ i; } ;
struct TYPE_74__ {scalar_t__ type; TYPE_7__ u; } ;
struct TYPE_75__ {int /*<<< orphan*/  forced_local; int /*<<< orphan*/  def_regular; TYPE_8__ root; } ;
struct mips_elf_link_hash_entry {unsigned char tls_type; void* need_fn_stub; void* no_fn_stub; void* is_branch_target; void* readonly_reloc; int /*<<< orphan*/  possibly_dynamic_relocs; TYPE_9__ root; void* is_relocation_target; TYPE_11__* call_stub; TYPE_11__* call_fp_stub; TYPE_11__* fn_stub; } ;
struct TYPE_69__ {scalar_t__ link; } ;
struct TYPE_70__ {TYPE_3__ i; } ;
struct TYPE_71__ {scalar_t__ type; TYPE_4__ u; } ;
struct elf_link_hash_entry {int needs_plt; int /*<<< orphan*/  type; TYPE_5__ root; } ;
struct elf_backend_data {TYPE_2__* s; } ;
struct bfd_link_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  shared; int /*<<< orphan*/  symbolic; int /*<<< orphan*/  keep_memory; scalar_t__ relocatable; } ;
typedef  unsigned long bfd_size_type ;
typedef  void* bfd_boolean ;
struct TYPE_59__ {TYPE_11__* sections; } ;
typedef  TYPE_10__ bfd ;
struct TYPE_60__ {int flags; scalar_t__ reloc_count; struct TYPE_60__* next; } ;
typedef  TYPE_11__ asection ;
struct TYPE_68__ {TYPE_10__* dynobj; } ;
struct TYPE_67__ {TYPE_13__* relocs; } ;
struct TYPE_61__ {size_t sh_info; } ;
struct TYPE_66__ {TYPE_11__** local_call_stubs; TYPE_11__** local_stubs; TYPE_12__ symtab_hdr; } ;
struct TYPE_65__ {int int_rels_per_ext_rel; } ;
struct TYPE_64__ {struct mips_got_info* got_info; } ;
struct TYPE_63__ {TYPE_1__ u; } ;
struct TYPE_62__ {scalar_t__ r_offset; int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_12__ Elf_Internal_Shdr ;
typedef  TYPE_13__ Elf_Internal_Rela ;
typedef  int /*<<< orphan*/  Elf32_External_crinfo ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ CALL_FP_STUB_P (char const*) ; 
 scalar_t__ CALL_STUB_P (char const*) ; 
 int /*<<< orphan*/  DF_STATIC_TLS ; 
 int /*<<< orphan*/  DF_TEXTREL ; 
 unsigned long ELF_R_SYM (TYPE_10__*,int /*<<< orphan*/ ) ; 
 unsigned int ELF_R_TYPE (TYPE_10__*,int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 scalar_t__ FN_STUB_P (char const*) ; 
 unsigned char GOT_TLS_GD ; 
 unsigned char GOT_TLS_IE ; 
 unsigned char GOT_TLS_LDM ; 
 scalar_t__ MIPS_ELF_READONLY_SECTION (TYPE_11__*) ; 
 size_t NUM_SHDR_ENTRIES (TYPE_12__*) ; 
 unsigned int R_MIPS16_26 ; 
#define  R_MIPS_26 150 
#define  R_MIPS_32 149 
#define  R_MIPS_64 148 
#define  R_MIPS_CALL16 147 
#define  R_MIPS_CALL_HI16 146 
#define  R_MIPS_CALL_LO16 145 
#define  R_MIPS_GNU_VTENTRY 144 
#define  R_MIPS_GNU_VTINHERIT 143 
#define  R_MIPS_GOT16 142 
#define  R_MIPS_GOT_DISP 141 
#define  R_MIPS_GOT_HI16 140 
#define  R_MIPS_GOT_LO16 139 
#define  R_MIPS_GOT_OFST 138 
#define  R_MIPS_GOT_PAGE 137 
#define  R_MIPS_GPREL16 136 
#define  R_MIPS_GPREL32 135 
#define  R_MIPS_JALR 134 
#define  R_MIPS_LITERAL 133 
#define  R_MIPS_PC16 132 
#define  R_MIPS_REL32 131 
#define  R_MIPS_TLS_GD 130 
#define  R_MIPS_TLS_GOTTPREL 129 
#define  R_MIPS_TLS_LDM 128 
 int SEC_ALLOC ; 
 int SEC_EXCLUDE ; 
 int SEC_KEEP ; 
 int SEC_RELOC ; 
 int /*<<< orphan*/  SGI_COMPAT (TYPE_10__*) ; 
 int /*<<< orphan*/  STT_FUNC ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_13__* _bfd_elf_link_read_relocs (TYPE_10__*,TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,TYPE_10__*,unsigned long) ; 
 int /*<<< orphan*/  bfd_elf_gc_record_vtentry (TYPE_10__*,TYPE_11__*,struct elf_link_hash_entry*,scalar_t__) ; 
 int /*<<< orphan*/  bfd_elf_gc_record_vtinherit (TYPE_10__*,TYPE_11__*,struct elf_link_hash_entry*,scalar_t__) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 char* bfd_get_section_name (TYPE_10__*,TYPE_11__*) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_11__** bfd_zalloc (TYPE_10__*,unsigned long) ; 
 scalar_t__ elf_bad_symtab (TYPE_10__*) ; 
 TYPE_37__* elf_hash_table (struct bfd_link_info*) ; 
 TYPE_35__* elf_section_data (TYPE_11__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (TYPE_10__*) ; 
 TYPE_32__* elf_tdata (TYPE_10__*) ; 
 int /*<<< orphan*/  free (TYPE_13__*) ; 
 struct elf_backend_data* get_elf_backend_data (TYPE_10__*) ; 
 scalar_t__ is_gott_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 scalar_t__ mips16_stub_section_p (TYPE_10__*,TYPE_11__*) ; 
 int /*<<< orphan*/  mips_elf_allocate_dynamic_relocations (TYPE_10__*,struct bfd_link_info*,int) ; 
 int /*<<< orphan*/  mips_elf_create_got_section (TYPE_10__*,struct bfd_link_info*,void*) ; 
 struct mips_got_info* mips_elf_got_info (TYPE_10__*,TYPE_11__**) ; 
 TYPE_11__* mips_elf_got_section (TYPE_10__*,void*) ; 
 struct mips_elf_link_hash_table* mips_elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  mips_elf_record_global_got_symbol (struct elf_link_hash_entry*,TYPE_10__*,struct bfd_link_info*,struct mips_got_info*,unsigned char) ; 
 int /*<<< orphan*/  mips_elf_record_local_got_symbol (TYPE_10__*,unsigned long,int /*<<< orphan*/ ,struct mips_got_info*,unsigned char) ; 
 TYPE_11__* mips_elf_rel_dyn_section (struct bfd_link_info*,void*) ; 
 TYPE_17__* mips_elf_section_data (TYPE_11__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_10__*,...) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_10__*,unsigned long) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_10__*,unsigned long) ; 

bfd_boolean
_bfd_mips_elf_check_relocs (bfd *abfd, struct bfd_link_info *info,
			    asection *sec, const Elf_Internal_Rela *relocs)
{
  const char *name;
  bfd *dynobj;
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  struct mips_got_info *g;
  size_t extsymoff;
  const Elf_Internal_Rela *rel;
  const Elf_Internal_Rela *rel_end;
  asection *sgot;
  asection *sreloc;
  const struct elf_backend_data *bed;
  struct mips_elf_link_hash_table *htab;

  if (info->relocatable)
    return TRUE;

  htab = mips_elf_hash_table (info);
  dynobj = elf_hash_table (info)->dynobj;
  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (abfd);
  extsymoff = (elf_bad_symtab (abfd)) ? 0 : symtab_hdr->sh_info;

  /* Check for the mips16 stub sections.  */

  name = bfd_get_section_name (abfd, sec);
  if (FN_STUB_P (name))
    {
      unsigned long r_symndx;

      /* Look at the relocation information to figure out which symbol
         this is for.  */

      r_symndx = ELF_R_SYM (abfd, relocs->r_info);

      if (r_symndx < extsymoff
	  || sym_hashes[r_symndx - extsymoff] == NULL)
	{
	  asection *o;

	  /* This stub is for a local symbol.  This stub will only be
             needed if there is some relocation in this BFD, other
             than a 16 bit function call, which refers to this symbol.  */
	  for (o = abfd->sections; o != NULL; o = o->next)
	    {
	      Elf_Internal_Rela *sec_relocs;
	      const Elf_Internal_Rela *r, *rend;

	      /* We can ignore stub sections when looking for relocs.  */
	      if ((o->flags & SEC_RELOC) == 0
		  || o->reloc_count == 0
		  || mips16_stub_section_p (abfd, o))
		continue;

	      sec_relocs
		= _bfd_elf_link_read_relocs (abfd, o, NULL, NULL,
					     info->keep_memory);
	      if (sec_relocs == NULL)
		return FALSE;

	      rend = sec_relocs + o->reloc_count;
	      for (r = sec_relocs; r < rend; r++)
		if (ELF_R_SYM (abfd, r->r_info) == r_symndx
		    && ELF_R_TYPE (abfd, r->r_info) != R_MIPS16_26)
		  break;

	      if (elf_section_data (o)->relocs != sec_relocs)
		free (sec_relocs);

	      if (r < rend)
		break;
	    }

	  if (o == NULL)
	    {
	      /* There is no non-call reloc for this stub, so we do
                 not need it.  Since this function is called before
                 the linker maps input sections to output sections, we
                 can easily discard it by setting the SEC_EXCLUDE
                 flag.  */
	      sec->flags |= SEC_EXCLUDE;
	      return TRUE;
	    }

	  /* Record this stub in an array of local symbol stubs for
             this BFD.  */
	  if (elf_tdata (abfd)->local_stubs == NULL)
	    {
	      unsigned long symcount;
	      asection **n;
	      bfd_size_type amt;

	      if (elf_bad_symtab (abfd))
		symcount = NUM_SHDR_ENTRIES (symtab_hdr);
	      else
		symcount = symtab_hdr->sh_info;
	      amt = symcount * sizeof (asection *);
	      n = bfd_zalloc (abfd, amt);
	      if (n == NULL)
		return FALSE;
	      elf_tdata (abfd)->local_stubs = n;
	    }

	  sec->flags |= SEC_KEEP;
	  elf_tdata (abfd)->local_stubs[r_symndx] = sec;

	  /* We don't need to set mips16_stubs_seen in this case.
             That flag is used to see whether we need to look through
             the global symbol table for stubs.  We don't need to set
             it here, because we just have a local stub.  */
	}
      else
	{
	  struct mips_elf_link_hash_entry *h;

	  h = ((struct mips_elf_link_hash_entry *)
	       sym_hashes[r_symndx - extsymoff]);

	  while (h->root.root.type == bfd_link_hash_indirect
		 || h->root.root.type == bfd_link_hash_warning)
	    h = (struct mips_elf_link_hash_entry *) h->root.root.u.i.link;

	  /* H is the symbol this stub is for.  */

	  /* If we already have an appropriate stub for this function, we
	     don't need another one, so we can discard this one.  Since
	     this function is called before the linker maps input sections
	     to output sections, we can easily discard it by setting the
	     SEC_EXCLUDE flag.  */
	  if (h->fn_stub != NULL)
	    {
	      sec->flags |= SEC_EXCLUDE;
	      return TRUE;
	    }

	  sec->flags |= SEC_KEEP;
	  h->fn_stub = sec;
	  mips_elf_hash_table (info)->mips16_stubs_seen = TRUE;
	}
    }
  else if (CALL_STUB_P (name) || CALL_FP_STUB_P (name))
    {
      unsigned long r_symndx;
      struct mips_elf_link_hash_entry *h;
      asection **loc;

      /* Look at the relocation information to figure out which symbol
         this is for.  */

      r_symndx = ELF_R_SYM (abfd, relocs->r_info);

      if (r_symndx < extsymoff
	  || sym_hashes[r_symndx - extsymoff] == NULL)
	{
	  asection *o;

	  /* This stub is for a local symbol.  This stub will only be
             needed if there is some relocation (R_MIPS16_26) in this BFD
             that refers to this symbol.  */
	  for (o = abfd->sections; o != NULL; o = o->next)
	    {
	      Elf_Internal_Rela *sec_relocs;
	      const Elf_Internal_Rela *r, *rend;

	      /* We can ignore stub sections when looking for relocs.  */
	      if ((o->flags & SEC_RELOC) == 0
		  || o->reloc_count == 0
		  || mips16_stub_section_p (abfd, o))
		continue;

	      sec_relocs
		= _bfd_elf_link_read_relocs (abfd, o, NULL, NULL,
					     info->keep_memory);
	      if (sec_relocs == NULL)
		return FALSE;

	      rend = sec_relocs + o->reloc_count;
	      for (r = sec_relocs; r < rend; r++)
		if (ELF_R_SYM (abfd, r->r_info) == r_symndx
		    && ELF_R_TYPE (abfd, r->r_info) == R_MIPS16_26)
		    break;

	      if (elf_section_data (o)->relocs != sec_relocs)
		free (sec_relocs);

	      if (r < rend)
		break;
	    }

	  if (o == NULL)
	    {
	      /* There is no non-call reloc for this stub, so we do
                 not need it.  Since this function is called before
                 the linker maps input sections to output sections, we
                 can easily discard it by setting the SEC_EXCLUDE
                 flag.  */
	      sec->flags |= SEC_EXCLUDE;
	      return TRUE;
	    }

	  /* Record this stub in an array of local symbol call_stubs for
             this BFD.  */
	  if (elf_tdata (abfd)->local_call_stubs == NULL)
	    {
	      unsigned long symcount;
	      asection **n;
	      bfd_size_type amt;

	      if (elf_bad_symtab (abfd))
		symcount = NUM_SHDR_ENTRIES (symtab_hdr);
	      else
		symcount = symtab_hdr->sh_info;
	      amt = symcount * sizeof (asection *);
	      n = bfd_zalloc (abfd, amt);
	      if (n == NULL)
		return FALSE;
	      elf_tdata (abfd)->local_call_stubs = n;
	    }

	  sec->flags |= SEC_KEEP;
	  elf_tdata (abfd)->local_call_stubs[r_symndx] = sec;

	  /* We don't need to set mips16_stubs_seen in this case.
             That flag is used to see whether we need to look through
             the global symbol table for stubs.  We don't need to set
             it here, because we just have a local stub.  */
	}
      else
	{
	  h = ((struct mips_elf_link_hash_entry *)
	       sym_hashes[r_symndx - extsymoff]);
	  
	  /* H is the symbol this stub is for.  */
	  
	  if (CALL_FP_STUB_P (name))
	    loc = &h->call_fp_stub;
	  else
	    loc = &h->call_stub;
	  
	  /* If we already have an appropriate stub for this function, we
	     don't need another one, so we can discard this one.  Since
	     this function is called before the linker maps input sections
	     to output sections, we can easily discard it by setting the
	     SEC_EXCLUDE flag.  */
	  if (*loc != NULL)
	    {
	      sec->flags |= SEC_EXCLUDE;
	      return TRUE;
	    }

	  sec->flags |= SEC_KEEP;
	  *loc = sec;
	  mips_elf_hash_table (info)->mips16_stubs_seen = TRUE;
	}
    }

  if (dynobj == NULL)
    {
      sgot = NULL;
      g = NULL;
    }
  else
    {
      sgot = mips_elf_got_section (dynobj, FALSE);
      if (sgot == NULL)
	g = NULL;
      else
	{
	  BFD_ASSERT (mips_elf_section_data (sgot) != NULL);
	  g = mips_elf_section_data (sgot)->u.got_info;
	  BFD_ASSERT (g != NULL);
	}
    }

  sreloc = NULL;
  bed = get_elf_backend_data (abfd);
  rel_end = relocs + sec->reloc_count * bed->s->int_rels_per_ext_rel;
  for (rel = relocs; rel < rel_end; ++rel)
    {
      unsigned long r_symndx;
      unsigned int r_type;
      struct elf_link_hash_entry *h;

      r_symndx = ELF_R_SYM (abfd, rel->r_info);
      r_type = ELF_R_TYPE (abfd, rel->r_info);

      if (r_symndx < extsymoff)
	h = NULL;
      else if (r_symndx >= extsymoff + NUM_SHDR_ENTRIES (symtab_hdr))
	{
	  (*_bfd_error_handler)
	    (_("%B: Malformed reloc detected for section %s"),
	     abfd, name);
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}
      else
	{
	  h = sym_hashes[r_symndx - extsymoff];

	  /* This may be an indirect symbol created because of a version.  */
	  if (h != NULL)
	    {
	      while (h->root.type == bfd_link_hash_indirect)
		h = (struct elf_link_hash_entry *) h->root.u.i.link;
	    }
	}

      /* Some relocs require a global offset table.  */
      if (dynobj == NULL || sgot == NULL)
	{
	  switch (r_type)
	    {
	    case R_MIPS_GOT16:
	    case R_MIPS_CALL16:
	    case R_MIPS_CALL_HI16:
	    case R_MIPS_CALL_LO16:
	    case R_MIPS_GOT_HI16:
	    case R_MIPS_GOT_LO16:
	    case R_MIPS_GOT_PAGE:
	    case R_MIPS_GOT_OFST:
	    case R_MIPS_GOT_DISP:
	    case R_MIPS_TLS_GOTTPREL:
	    case R_MIPS_TLS_GD:
	    case R_MIPS_TLS_LDM:
	      if (dynobj == NULL)
		elf_hash_table (info)->dynobj = dynobj = abfd;
	      if (! mips_elf_create_got_section (dynobj, info, FALSE))
		return FALSE;
	      g = mips_elf_got_info (dynobj, &sgot);
	      if (htab->is_vxworks && !info->shared)
		{
		  (*_bfd_error_handler)
		    (_("%B: GOT reloc at 0x%lx not expected in executables"),
		     abfd, (unsigned long) rel->r_offset);
		  bfd_set_error (bfd_error_bad_value);
		  return FALSE;
		}
	      break;

	    case R_MIPS_32:
	    case R_MIPS_REL32:
	    case R_MIPS_64:
	      /* In VxWorks executables, references to external symbols
		 are handled using copy relocs or PLT stubs, so there's
		 no need to add a dynamic relocation here.  */
	      if (dynobj == NULL
		  && (info->shared || (h != NULL && !htab->is_vxworks))
		  && (sec->flags & SEC_ALLOC) != 0)
		elf_hash_table (info)->dynobj = dynobj = abfd;
	      break;

	    default:
	      break;
	    }
	}

      if (h)
	{
	  ((struct mips_elf_link_hash_entry *) h)->is_relocation_target = TRUE;

	  /* Relocations against the special VxWorks __GOTT_BASE__ and
	     __GOTT_INDEX__ symbols must be left to the loader.  Allocate
	     room for them in .rela.dyn.  */
	  if (is_gott_symbol (info, h))
	    {
	      if (sreloc == NULL)
		{
		  sreloc = mips_elf_rel_dyn_section (info, TRUE);
		  if (sreloc == NULL)
		    return FALSE;
		}
	      mips_elf_allocate_dynamic_relocations (dynobj, info, 1);
	      if (MIPS_ELF_READONLY_SECTION (sec))
		/* We tell the dynamic linker that there are
		   relocations against the text segment.  */
		info->flags |= DF_TEXTREL;
	    }
	}
      else if (r_type == R_MIPS_CALL_LO16
	       || r_type == R_MIPS_GOT_LO16
	       || r_type == R_MIPS_GOT_DISP
	       || (r_type == R_MIPS_GOT16 && htab->is_vxworks))
	{
	  /* We may need a local GOT entry for this relocation.  We
	     don't count R_MIPS_GOT_PAGE because we can estimate the
	     maximum number of pages needed by looking at the size of
	     the segment.  Similar comments apply to R_MIPS_GOT16 and
	     R_MIPS_CALL16, except on VxWorks, where GOT relocations
	     always evaluate to "G".  We don't count R_MIPS_GOT_HI16, or
	     R_MIPS_CALL_HI16 because these are always followed by an
	     R_MIPS_GOT_LO16 or R_MIPS_CALL_LO16.  */
	  if (! mips_elf_record_local_got_symbol (abfd, r_symndx,
						  rel->r_addend, g, 0))
	    return FALSE;
	}

      switch (r_type)
	{
	case R_MIPS_CALL16:
	  if (h == NULL)
	    {
	      (*_bfd_error_handler)
		(_("%B: CALL16 reloc at 0x%lx not against global symbol"),
		 abfd, (unsigned long) rel->r_offset);
	      bfd_set_error (bfd_error_bad_value);
	      return FALSE;
	    }
	  /* Fall through.  */

	case R_MIPS_CALL_HI16:
	case R_MIPS_CALL_LO16:
	  if (h != NULL)
	    {
	      /* VxWorks call relocations point the function's .got.plt
		 entry, which will be allocated by adjust_dynamic_symbol.
		 Otherwise, this symbol requires a global GOT entry.  */
	      if (!htab->is_vxworks
		  && !mips_elf_record_global_got_symbol (h, abfd, info, g, 0))
		return FALSE;

	      /* We need a stub, not a plt entry for the undefined
		 function.  But we record it as if it needs plt.  See
		 _bfd_elf_adjust_dynamic_symbol.  */
	      h->needs_plt = 1;
	      h->type = STT_FUNC;
	    }
	  break;

	case R_MIPS_GOT_PAGE:
	  /* If this is a global, overridable symbol, GOT_PAGE will
	     decay to GOT_DISP, so we'll need a GOT entry for it.  */
	  if (h == NULL)
	    break;
	  else
	    {
	      struct mips_elf_link_hash_entry *hmips =
		(struct mips_elf_link_hash_entry *) h;

	      while (hmips->root.root.type == bfd_link_hash_indirect
		     || hmips->root.root.type == bfd_link_hash_warning)
		hmips = (struct mips_elf_link_hash_entry *)
		  hmips->root.root.u.i.link;

	      if (hmips->root.def_regular
		  && ! (info->shared && ! info->symbolic
			&& ! hmips->root.forced_local))
		break;
	    }
	  /* Fall through.  */

	case R_MIPS_GOT16:
	case R_MIPS_GOT_HI16:
	case R_MIPS_GOT_LO16:
	case R_MIPS_GOT_DISP:
	  if (h && ! mips_elf_record_global_got_symbol (h, abfd, info, g, 0))
	    return FALSE;
	  break;

	case R_MIPS_TLS_GOTTPREL:
	  if (info->shared)
	    info->flags |= DF_STATIC_TLS;
	  /* Fall through */

	case R_MIPS_TLS_LDM:
	  if (r_type == R_MIPS_TLS_LDM)
	    {
	      r_symndx = 0;
	      h = NULL;
	    }
	  /* Fall through */

	case R_MIPS_TLS_GD:
	  /* This symbol requires a global offset table entry, or two
	     for TLS GD relocations.  */
	  {
	    unsigned char flag = (r_type == R_MIPS_TLS_GD
				  ? GOT_TLS_GD
				  : r_type == R_MIPS_TLS_LDM
				  ? GOT_TLS_LDM
				  : GOT_TLS_IE);
	    if (h != NULL)
	      {
		struct mips_elf_link_hash_entry *hmips =
		  (struct mips_elf_link_hash_entry *) h;
		hmips->tls_type |= flag;

		if (h && ! mips_elf_record_global_got_symbol (h, abfd, info, g, flag))
		  return FALSE;
	      }
	    else
	      {
		BFD_ASSERT (flag == GOT_TLS_LDM || r_symndx != 0);

		if (! mips_elf_record_local_got_symbol (abfd, r_symndx,
							rel->r_addend, g, flag))
		  return FALSE;
	      }
	  }
	  break;

	case R_MIPS_32:
	case R_MIPS_REL32:
	case R_MIPS_64:
	  /* In VxWorks executables, references to external symbols
	     are handled using copy relocs or PLT stubs, so there's
	     no need to add a .rela.dyn entry for this relocation.  */
	  if ((info->shared || (h != NULL && !htab->is_vxworks))
	      && (sec->flags & SEC_ALLOC) != 0)
	    {
	      if (sreloc == NULL)
		{
		  sreloc = mips_elf_rel_dyn_section (info, TRUE);
		  if (sreloc == NULL)
		    return FALSE;
		}
	      if (info->shared)
		{
		  /* When creating a shared object, we must copy these
		     reloc types into the output file as R_MIPS_REL32
		     relocs.  Make room for this reloc in .rel(a).dyn.  */
		  mips_elf_allocate_dynamic_relocations (dynobj, info, 1);
		  if (MIPS_ELF_READONLY_SECTION (sec))
		    /* We tell the dynamic linker that there are
		       relocations against the text segment.  */
		    info->flags |= DF_TEXTREL;
		}
	      else
		{
		  struct mips_elf_link_hash_entry *hmips;

		  /* We only need to copy this reloc if the symbol is
                     defined in a dynamic object.  */
		  hmips = (struct mips_elf_link_hash_entry *) h;
		  ++hmips->possibly_dynamic_relocs;
		  if (MIPS_ELF_READONLY_SECTION (sec))
		    /* We need it to tell the dynamic linker if there
		       are relocations against the text segment.  */
		    hmips->readonly_reloc = TRUE;
		}

	      /* Even though we don't directly need a GOT entry for
		 this symbol, a symbol must have a dynamic symbol
		 table index greater that DT_MIPS_GOTSYM if there are
		 dynamic relocations against it.  This does not apply
		 to VxWorks, which does not have the usual coupling
		 between global GOT entries and .dynsym entries.  */
	      if (h != NULL && !htab->is_vxworks)
		{
		  if (dynobj == NULL)
		    elf_hash_table (info)->dynobj = dynobj = abfd;
		  if (! mips_elf_create_got_section (dynobj, info, TRUE))
		    return FALSE;
		  g = mips_elf_got_info (dynobj, &sgot);
		  if (! mips_elf_record_global_got_symbol (h, abfd, info, g, 0))
		    return FALSE;
		}
	    }

	  if (SGI_COMPAT (abfd))
	    mips_elf_hash_table (info)->compact_rel_size +=
	      sizeof (Elf32_External_crinfo);
	  break;

	case R_MIPS_PC16:
	  if (h)
	    ((struct mips_elf_link_hash_entry *) h)->is_branch_target = TRUE;
	  break;

	case R_MIPS_26:
	  if (h)
	    ((struct mips_elf_link_hash_entry *) h)->is_branch_target = TRUE;
	  /* Fall through.  */

	case R_MIPS_GPREL16:
	case R_MIPS_LITERAL:
	case R_MIPS_GPREL32:
	  if (SGI_COMPAT (abfd))
	    mips_elf_hash_table (info)->compact_rel_size +=
	      sizeof (Elf32_External_crinfo);
	  break;

	  /* This relocation describes the C++ object vtable hierarchy.
	     Reconstruct it for later use during GC.  */
	case R_MIPS_GNU_VTINHERIT:
	  if (!bfd_elf_gc_record_vtinherit (abfd, sec, h, rel->r_offset))
	    return FALSE;
	  break;

	  /* This relocation describes which C++ vtable entries are actually
	     used.  Record for later use during GC.  */
	case R_MIPS_GNU_VTENTRY:
	  if (!bfd_elf_gc_record_vtentry (abfd, sec, h, rel->r_offset))
	    return FALSE;
	  break;

	default:
	  break;
	}

      /* We must not create a stub for a symbol that has relocations
	 related to taking the function's address.  This doesn't apply to
	 VxWorks, where CALL relocs refer to a .got.plt entry instead of
	 a normal .got entry.  */
      if (!htab->is_vxworks && h != NULL)
	switch (r_type)
	  {
	  default:
	    ((struct mips_elf_link_hash_entry *) h)->no_fn_stub = TRUE;
	    break;
	  case R_MIPS_CALL16:
	  case R_MIPS_CALL_HI16:
	  case R_MIPS_CALL_LO16:
	  case R_MIPS_JALR:
	    break;
	  }

      /* If this reloc is not a 16 bit call, and it has a global
         symbol, then we will need the fn_stub if there is one.
         References from a stub section do not count.  */
      if (h != NULL
	  && r_type != R_MIPS16_26
	  && !mips16_stub_section_p (abfd, sec))
	{
	  struct mips_elf_link_hash_entry *mh;

	  mh = (struct mips_elf_link_hash_entry *) h;
	  mh->need_fn_stub = TRUE;
	}
    }

  return TRUE;
}