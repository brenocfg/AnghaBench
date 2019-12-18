#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_52__   TYPE_9__ ;
typedef  struct TYPE_51__   TYPE_8__ ;
typedef  struct TYPE_50__   TYPE_7__ ;
typedef  struct TYPE_49__   TYPE_6__ ;
typedef  struct TYPE_48__   TYPE_5__ ;
typedef  struct TYPE_47__   TYPE_4__ ;
typedef  struct TYPE_46__   TYPE_3__ ;
typedef  struct TYPE_45__   TYPE_2__ ;
typedef  struct TYPE_44__   TYPE_23__ ;
typedef  struct TYPE_43__   TYPE_22__ ;
typedef  struct TYPE_42__   TYPE_20__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_19__ ;
typedef  struct TYPE_39__   TYPE_16__ ;
typedef  struct TYPE_38__   TYPE_15__ ;
typedef  struct TYPE_37__   TYPE_14__ ;
typedef  struct TYPE_36__   TYPE_13__ ;

/* Type definitions */
struct TYPE_43__ {int /*<<< orphan*/ * dynobj; struct elf_link_hash_entry* hgot; } ;
struct ppc_elf_link_hash_table {TYPE_22__ elf; int /*<<< orphan*/  sym_sec; int /*<<< orphan*/ * old_bfd; void* plt_type; TYPE_16__* sdata; int /*<<< orphan*/ * got; } ;
struct ppc_elf_dyn_relocs {int count; int pc_count; TYPE_7__* sec; struct ppc_elf_dyn_relocs* next; } ;
struct TYPE_47__ {char* string; } ;
struct TYPE_41__ {scalar_t__ link; } ;
struct TYPE_45__ {TYPE_1__ i; } ;
struct TYPE_48__ {scalar_t__ type; TYPE_4__ root; TYPE_2__ u; } ;
struct TYPE_46__ {int refcount; } ;
struct elf_link_hash_entry {int non_got_ref; int needs_plt; TYPE_5__ root; int /*<<< orphan*/  def_regular; TYPE_3__ got; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; int /*<<< orphan*/  symbolic; int /*<<< orphan*/  pie; int /*<<< orphan*/  flags; int /*<<< orphan*/  executable; scalar_t__ relocatable; } ;
typedef  int flagword ;
typedef  enum elf_ppc_reloc_type { ____Placeholder_elf_ppc_reloc_type } elf_ppc_reloc_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  void* bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_50__ {int flags; int reloc_count; int has_tls_get_addr_call; int has_tls_reloc; } ;
typedef  TYPE_7__ asection ;
struct TYPE_52__ {int /*<<< orphan*/  r_addend; scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_51__ {unsigned long sh_info; } ;
struct TYPE_49__ {int /*<<< orphan*/  sh_name; } ;
struct TYPE_44__ {int /*<<< orphan*/  e_shstrndx; } ;
struct TYPE_42__ {int /*<<< orphan*/  local_dynrel; TYPE_7__* sreloc; TYPE_6__ rel_hdr; } ;
struct TYPE_40__ {TYPE_8__ symtab_hdr; } ;
struct TYPE_39__ {int /*<<< orphan*/ * sym; int /*<<< orphan*/ * section; } ;
struct TYPE_38__ {int tls_mask; struct ppc_elf_dyn_relocs* dyn_relocs; void* has_sda_refs; } ;
struct TYPE_37__ {int /*<<< orphan*/  name; } ;
struct TYPE_36__ {int makes_plt_call; int has_rel16; } ;
typedef  TYPE_8__ Elf_Internal_Shdr ;
typedef  TYPE_9__ Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  CONST_STRNEQ (char const*,char*) ; 
 int /*<<< orphan*/  DF_STATIC_TLS ; 
 unsigned long ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELIMINATE_COPY_RELOCS ; 
 void* FALSE ; 
 void* PLT_OLD ; 
 void* PLT_UNSET ; 
#define  R_PPC_ADDR14 219 
#define  R_PPC_ADDR14_BRNTAKEN 218 
#define  R_PPC_ADDR14_BRTAKEN 217 
#define  R_PPC_ADDR16 216 
#define  R_PPC_ADDR16_HA 215 
#define  R_PPC_ADDR16_HI 214 
#define  R_PPC_ADDR16_LO 213 
#define  R_PPC_ADDR24 212 
#define  R_PPC_ADDR30 211 
#define  R_PPC_ADDR32 210 
#define  R_PPC_COPY 209 
#define  R_PPC_DTPMOD32 208 
#define  R_PPC_DTPREL16 207 
#define  R_PPC_DTPREL16_HA 206 
#define  R_PPC_DTPREL16_HI 205 
#define  R_PPC_DTPREL16_LO 204 
#define  R_PPC_DTPREL32 203 
#define  R_PPC_EMB_BIT_FLD 202 
#define  R_PPC_EMB_MRKREF 201 
#define  R_PPC_EMB_NADDR16 200 
#define  R_PPC_EMB_NADDR16_HA 199 
#define  R_PPC_EMB_NADDR16_HI 198 
#define  R_PPC_EMB_NADDR16_LO 197 
#define  R_PPC_EMB_NADDR32 196 
#define  R_PPC_EMB_RELSDA 195 
#define  R_PPC_EMB_RELSEC16 194 
#define  R_PPC_EMB_RELST_HA 193 
#define  R_PPC_EMB_RELST_HI 192 
#define  R_PPC_EMB_RELST_LO 191 
#define  R_PPC_EMB_SDA21 190 
#define  R_PPC_EMB_SDA2I16 189 
#define  R_PPC_EMB_SDA2REL 188 
#define  R_PPC_EMB_SDAI16 187 
#define  R_PPC_GLOB_DAT 186 
#define  R_PPC_GNU_VTENTRY 185 
#define  R_PPC_GNU_VTINHERIT 184 
#define  R_PPC_GOT16 183 
#define  R_PPC_GOT16_HA 182 
#define  R_PPC_GOT16_HI 181 
#define  R_PPC_GOT16_LO 180 
#define  R_PPC_GOT_DTPREL16 179 
#define  R_PPC_GOT_DTPREL16_HA 178 
#define  R_PPC_GOT_DTPREL16_HI 177 
#define  R_PPC_GOT_DTPREL16_LO 176 
#define  R_PPC_GOT_TLSGD16 175 
#define  R_PPC_GOT_TLSGD16_HA 174 
#define  R_PPC_GOT_TLSGD16_HI 173 
#define  R_PPC_GOT_TLSGD16_LO 172 
#define  R_PPC_GOT_TLSLD16 171 
#define  R_PPC_GOT_TLSLD16_HA 170 
#define  R_PPC_GOT_TLSLD16_HI 169 
#define  R_PPC_GOT_TLSLD16_LO 168 
#define  R_PPC_GOT_TPREL16 167 
#define  R_PPC_GOT_TPREL16_HA 166 
#define  R_PPC_GOT_TPREL16_HI 165 
#define  R_PPC_GOT_TPREL16_LO 164 
#define  R_PPC_JMP_SLOT 163 
#define  R_PPC_LOCAL24PC 162 
#define  R_PPC_NONE 161 
#define  R_PPC_PLT16_HA 160 
#define  R_PPC_PLT16_HI 159 
#define  R_PPC_PLT16_LO 158 
#define  R_PPC_PLT32 157 
#define  R_PPC_PLTREL24 156 
#define  R_PPC_PLTREL32 155 
#define  R_PPC_REL14 154 
#define  R_PPC_REL14_BRNTAKEN 153 
#define  R_PPC_REL14_BRTAKEN 152 
#define  R_PPC_REL16 151 
#define  R_PPC_REL16_HA 150 
#define  R_PPC_REL16_HI 149 
#define  R_PPC_REL16_LO 148 
#define  R_PPC_REL24 147 
#define  R_PPC_REL32 146 
#define  R_PPC_RELATIVE 145 
#define  R_PPC_SDAREL16 144 
#define  R_PPC_SECTOFF 143 
#define  R_PPC_SECTOFF_HA 142 
#define  R_PPC_SECTOFF_HI 141 
#define  R_PPC_SECTOFF_LO 140 
#define  R_PPC_TLS 139 
#define  R_PPC_TLSGD 138 
#define  R_PPC_TLSLD 137 
#define  R_PPC_TOC16 136 
#define  R_PPC_TPREL16 135 
#define  R_PPC_TPREL16_HA 134 
#define  R_PPC_TPREL16_HI 133 
#define  R_PPC_TPREL16_LO 132 
#define  R_PPC_TPREL32 131 
#define  R_PPC_UADDR16 130 
#define  R_PPC_UADDR32 129 
#define  R_PPC_max 128 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int TLS_DTPREL ; 
 int TLS_GD ; 
 int TLS_LD ; 
 int TLS_TLS ; 
 int TLS_TPREL ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_shared_reloc (int /*<<< orphan*/ *,int) ; 
 struct ppc_elf_dyn_relocs* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_elf_gc_record_vtentry (int /*<<< orphan*/ *,TYPE_7__*,struct elf_link_hash_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_elf_gc_record_vtinherit (int /*<<< orphan*/ *,TYPE_7__*,struct elf_link_hash_entry*,scalar_t__) ; 
 char* bfd_elf_string_from_elf_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 TYPE_7__* bfd_get_section_by_name (int /*<<< orphan*/ *,char const*) ; 
 char* bfd_get_section_name (int /*<<< orphan*/ *,TYPE_7__*) ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_7__* bfd_make_section_with_flags (int /*<<< orphan*/ *,char const*,int) ; 
 TYPE_7__* bfd_section_from_r_symndx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*,unsigned long) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/  create_sdata_sym (struct ppc_elf_link_hash_table*,TYPE_16__*) ; 
 int /*<<< orphan*/  elf_create_pointer_linker_section (int /*<<< orphan*/ *,TYPE_16__*,struct elf_link_hash_entry*,TYPE_9__ const*) ; 
 TYPE_23__* elf_elfheader (int /*<<< orphan*/ *) ; 
 struct elf_link_hash_entry* elf_link_hash_lookup (TYPE_22__*,char*,void*,void*,void*) ; 
 TYPE_20__* elf_section_data (TYPE_7__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_19__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  must_be_dyn_reloc (struct bfd_link_info*,int) ; 
 int /*<<< orphan*/  ppc_elf_create_got (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  ppc_elf_create_linker_section (int /*<<< orphan*/ *,struct bfd_link_info*,int,TYPE_16__*) ; 
 TYPE_15__* ppc_elf_hash_entry (struct elf_link_hash_entry*) ; 
 struct ppc_elf_link_hash_table* ppc_elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  ppc_elf_howto_init () ; 
 TYPE_14__** ppc_elf_howto_table ; 
 TYPE_13__* ppc_elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_local_sym_info (int /*<<< orphan*/ *,TYPE_8__*,unsigned long,int) ; 
 int /*<<< orphan*/  update_plt_info (int /*<<< orphan*/ *,struct elf_link_hash_entry*,TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
ppc_elf_check_relocs (bfd *abfd,
		      struct bfd_link_info *info,
		      asection *sec,
		      const Elf_Internal_Rela *relocs)
{
  struct ppc_elf_link_hash_table *htab;
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  const Elf_Internal_Rela *rel;
  const Elf_Internal_Rela *rel_end;
  asection *got2, *sreloc;
  struct elf_link_hash_entry *tga;

  if (info->relocatable)
    return TRUE;

  /* Don't do anything special with non-loaded, non-alloced sections.
     In particular, any relocs in such sections should not affect GOT
     and PLT reference counting (ie. we don't allow them to create GOT
     or PLT entries), there's no possibility or desire to optimize TLS
     relocs, and there's not much point in propagating relocs to shared
     libs that the dynamic linker won't relocate.  */
  if ((sec->flags & SEC_ALLOC) == 0)
    return TRUE;

#ifdef DEBUG
  _bfd_error_handler ("ppc_elf_check_relocs called for section %A in %B",
		      sec, abfd);
#endif

  /* Initialize howto table if not already done.  */
  if (!ppc_elf_howto_table[R_PPC_ADDR32])
    ppc_elf_howto_init ();

  htab = ppc_elf_hash_table (info);
  tga = elf_link_hash_lookup (&htab->elf, "__tls_get_addr",
			      FALSE, FALSE, TRUE);
  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (abfd);
  got2 = bfd_get_section_by_name (abfd, ".got2");
  sreloc = NULL;

  rel_end = relocs + sec->reloc_count;
  for (rel = relocs; rel < rel_end; rel++)
    {
      unsigned long r_symndx;
      enum elf_ppc_reloc_type r_type;
      struct elf_link_hash_entry *h;
      int tls_type;

      r_symndx = ELF32_R_SYM (rel->r_info);
      if (r_symndx < symtab_hdr->sh_info)
	h = NULL;
      else
	{
	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	}

      /* If a relocation refers to _GLOBAL_OFFSET_TABLE_, create the .got.
	 This shows up in particular in an R_PPC_ADDR32 in the eabi
	 startup code.  */
      if (h != NULL
	  && htab->got == NULL
	  && strcmp (h->root.root.string, "_GLOBAL_OFFSET_TABLE_") == 0)
	{
	  if (htab->elf.dynobj == NULL)
	    htab->elf.dynobj = abfd;
	  if (!ppc_elf_create_got (htab->elf.dynobj, info))
	    return FALSE;
	  BFD_ASSERT (h == htab->elf.hgot);
	}

      tls_type = 0;
      r_type = ELF32_R_TYPE (rel->r_info);
      if (h != NULL && h == tga)
	switch (r_type)
	  {
	  default:
	    break;

	  case R_PPC_PLTREL24:
	  case R_PPC_LOCAL24PC:
	  case R_PPC_REL24:
	  case R_PPC_REL14:
	  case R_PPC_REL14_BRTAKEN:
	  case R_PPC_REL14_BRNTAKEN:
	  case R_PPC_ADDR24:
	  case R_PPC_ADDR14:
	  case R_PPC_ADDR14_BRTAKEN:
	  case R_PPC_ADDR14_BRNTAKEN:
	    if (rel != relocs
		&& (ELF32_R_TYPE (rel[-1].r_info) == R_PPC_TLSGD
		    || ELF32_R_TYPE (rel[-1].r_info) == R_PPC_TLSLD))
	      /* We have a new-style __tls_get_addr call with a marker
		 reloc.  */
	      ;
	    else
	      /* Mark this section as having an old-style call.  */
	      sec->has_tls_get_addr_call = 1;
	    break;
	  }

      switch (r_type)
	{
	case R_PPC_TLSGD:
	case R_PPC_TLSLD:
	  /* These special tls relocs tie a call to __tls_get_addr with
	     its parameter symbol.  */
	  break;

	case R_PPC_GOT_TLSLD16:
	case R_PPC_GOT_TLSLD16_LO:
	case R_PPC_GOT_TLSLD16_HI:
	case R_PPC_GOT_TLSLD16_HA:
	  tls_type = TLS_TLS | TLS_LD;
	  goto dogottls;

	case R_PPC_GOT_TLSGD16:
	case R_PPC_GOT_TLSGD16_LO:
	case R_PPC_GOT_TLSGD16_HI:
	case R_PPC_GOT_TLSGD16_HA:
	  tls_type = TLS_TLS | TLS_GD;
	  goto dogottls;

	case R_PPC_GOT_TPREL16:
	case R_PPC_GOT_TPREL16_LO:
	case R_PPC_GOT_TPREL16_HI:
	case R_PPC_GOT_TPREL16_HA:
	  if (!info->executable)
	    info->flags |= DF_STATIC_TLS;
	  tls_type = TLS_TLS | TLS_TPREL;
	  goto dogottls;

	case R_PPC_GOT_DTPREL16:
	case R_PPC_GOT_DTPREL16_LO:
	case R_PPC_GOT_DTPREL16_HI:
	case R_PPC_GOT_DTPREL16_HA:
	  tls_type = TLS_TLS | TLS_DTPREL;
	dogottls:
	  sec->has_tls_reloc = 1;
	  /* Fall thru */

	  /* GOT16 relocations */
	case R_PPC_GOT16:
	case R_PPC_GOT16_LO:
	case R_PPC_GOT16_HI:
	case R_PPC_GOT16_HA:
	  /* This symbol requires a global offset table entry.  */
	  if (htab->got == NULL)
	    {
	      if (htab->elf.dynobj == NULL)
		htab->elf.dynobj = abfd;
	      if (!ppc_elf_create_got (htab->elf.dynobj, info))
		return FALSE;
	    }
	  if (h != NULL)
	    {
	      h->got.refcount += 1;
	      ppc_elf_hash_entry (h)->tls_mask |= tls_type;
	    }
	  else
	    /* This is a global offset table entry for a local symbol.  */
	    if (!update_local_sym_info (abfd, symtab_hdr, r_symndx, tls_type))
	      return FALSE;
	  break;

	  /* Indirect .sdata relocation.  */
	case R_PPC_EMB_SDAI16:
	  if (info->shared)
	    {
	      bad_shared_reloc (abfd, r_type);
	      return FALSE;
	    }
	  if (htab->sdata[0].section == NULL
	      && !ppc_elf_create_linker_section (abfd, info, 0,
						 &htab->sdata[0]))
	    return FALSE;
	  if (!elf_create_pointer_linker_section (abfd, &htab->sdata[0],
						  h, rel))
	    return FALSE;
	  if (h != NULL)
	    {
	      ppc_elf_hash_entry (h)->has_sda_refs = TRUE;
	      h->non_got_ref = TRUE;
	    }
	  break;

	  /* Indirect .sdata2 relocation.  */
	case R_PPC_EMB_SDA2I16:
	  if (info->shared)
	    {
	      bad_shared_reloc (abfd, r_type);
	      return FALSE;
	    }
	  if (htab->sdata[1].section == NULL
	      && !ppc_elf_create_linker_section (abfd, info, SEC_READONLY,
						 &htab->sdata[1]))
	    return FALSE;
	  if (!elf_create_pointer_linker_section (abfd, &htab->sdata[1],
						  h, rel))
	    return FALSE;
	  if (h != NULL)
	    {
	      ppc_elf_hash_entry (h)->has_sda_refs = TRUE;
	      h->non_got_ref = TRUE;
	    }
	  break;

	case R_PPC_SDAREL16:
	  if (info->shared)
	    {
	      bad_shared_reloc (abfd, r_type);
	      return FALSE;
	    }
	  if (htab->sdata[0].sym == NULL
	      && !create_sdata_sym (htab, &htab->sdata[0]))
	    return FALSE;
	  if (h != NULL)
	    {
	      ppc_elf_hash_entry (h)->has_sda_refs = TRUE;
	      h->non_got_ref = TRUE;
	    }
	  break;

	case R_PPC_EMB_SDA2REL:
	  if (info->shared)
	    {
	      bad_shared_reloc (abfd, r_type);
	      return FALSE;
	    }
	  if (htab->sdata[1].sym == NULL
	      && !create_sdata_sym (htab, &htab->sdata[1]))
	    return FALSE;
	  if (h != NULL)
	    {
	      ppc_elf_hash_entry (h)->has_sda_refs = TRUE;
	      h->non_got_ref = TRUE;
	    }
	  break;

	case R_PPC_EMB_SDA21:
	case R_PPC_EMB_RELSDA:
	  if (info->shared)
	    {
	      bad_shared_reloc (abfd, r_type);
	      return FALSE;
	    }
	  if (htab->sdata[0].sym == NULL
	      && !create_sdata_sym (htab, &htab->sdata[0]))
	    return FALSE;
	  if (htab->sdata[1].sym == NULL
	      && !create_sdata_sym (htab, &htab->sdata[1]))
	    return FALSE;
	  if (h != NULL)
	    {
	      ppc_elf_hash_entry (h)->has_sda_refs = TRUE;
	      h->non_got_ref = TRUE;
	    }
	  break;

	case R_PPC_EMB_NADDR32:
	case R_PPC_EMB_NADDR16:
	case R_PPC_EMB_NADDR16_LO:
	case R_PPC_EMB_NADDR16_HI:
	case R_PPC_EMB_NADDR16_HA:
	  if (info->shared)
	    {
	      bad_shared_reloc (abfd, r_type);
	      return FALSE;
	    }
	  if (h != NULL)
	    h->non_got_ref = TRUE;
	  break;

	case R_PPC_PLT32:
	case R_PPC_PLTREL24:
	case R_PPC_PLTREL32:
	case R_PPC_PLT16_LO:
	case R_PPC_PLT16_HI:
	case R_PPC_PLT16_HA:
#ifdef DEBUG
	  fprintf (stderr, "Reloc requires a PLT entry\n");
#endif
	  /* This symbol requires a procedure linkage table entry.  We
	     actually build the entry in finish_dynamic_symbol,
	     because this might be a case of linking PIC code without
	     linking in any dynamic objects, in which case we don't
	     need to generate a procedure linkage table after all.  */

	  if (h == NULL)
	    {
	      /* It does not make sense to have a procedure linkage
		 table entry for a local symbol.  */
	      (*_bfd_error_handler) (_("%B(%A+0x%lx): %s reloc against "
				       "local symbol"),
				     abfd,
				     sec,
				     (long) rel->r_offset,
				     ppc_elf_howto_table[r_type]->name);
	      bfd_set_error (bfd_error_bad_value);
	      return FALSE;
	    }
	  else
	    {
	      bfd_vma addend = 0;

	      if (r_type == R_PPC_PLTREL24)
		{
		  ppc_elf_tdata (abfd)->makes_plt_call = 1;
		  addend = rel->r_addend;
		}
	      h->needs_plt = 1;
	      if (!update_plt_info (abfd, h, got2, addend))
		return FALSE;
	    }
	  break;

	  /* The following relocations don't need to propagate the
	     relocation if linking a shared object since they are
	     section relative.  */
	case R_PPC_SECTOFF:
	case R_PPC_SECTOFF_LO:
	case R_PPC_SECTOFF_HI:
	case R_PPC_SECTOFF_HA:
	case R_PPC_DTPREL16:
	case R_PPC_DTPREL16_LO:
	case R_PPC_DTPREL16_HI:
	case R_PPC_DTPREL16_HA:
	case R_PPC_TOC16:
	  break;

	case R_PPC_REL16:
	case R_PPC_REL16_LO:
	case R_PPC_REL16_HI:
	case R_PPC_REL16_HA:
	  ppc_elf_tdata (abfd)->has_rel16 = 1;
	  break;

	  /* These are just markers.  */
	case R_PPC_TLS:
	case R_PPC_EMB_MRKREF:
	case R_PPC_NONE:
	case R_PPC_max:
	  break;

	  /* These should only appear in dynamic objects.  */
	case R_PPC_COPY:
	case R_PPC_GLOB_DAT:
	case R_PPC_JMP_SLOT:
	case R_PPC_RELATIVE:
	  break;

	  /* These aren't handled yet.  We'll report an error later.  */
	case R_PPC_ADDR30:
	case R_PPC_EMB_RELSEC16:
	case R_PPC_EMB_RELST_LO:
	case R_PPC_EMB_RELST_HI:
	case R_PPC_EMB_RELST_HA:
	case R_PPC_EMB_BIT_FLD:
	  break;

	  /* This refers only to functions defined in the shared library.  */
	case R_PPC_LOCAL24PC:
	  if (h != NULL && h == htab->elf.hgot && htab->plt_type == PLT_UNSET)
	    {
	      htab->plt_type = PLT_OLD;
	      htab->old_bfd = abfd;
	    }
	  break;

	  /* This relocation describes the C++ object vtable hierarchy.
	     Reconstruct it for later use during GC.  */
	case R_PPC_GNU_VTINHERIT:
	  if (!bfd_elf_gc_record_vtinherit (abfd, sec, h, rel->r_offset))
	    return FALSE;
	  break;

	  /* This relocation describes which C++ vtable entries are actually
	     used.  Record for later use during GC.  */
	case R_PPC_GNU_VTENTRY:
	  if (!bfd_elf_gc_record_vtentry (abfd, sec, h, rel->r_addend))
	    return FALSE;
	  break;

	  /* We shouldn't really be seeing these.  */
	case R_PPC_TPREL32:
	case R_PPC_TPREL16:
	case R_PPC_TPREL16_LO:
	case R_PPC_TPREL16_HI:
	case R_PPC_TPREL16_HA:
	  if (!info->executable)
	    info->flags |= DF_STATIC_TLS;
	  goto dodyn;

	  /* Nor these.  */
	case R_PPC_DTPMOD32:
	case R_PPC_DTPREL32:
	  goto dodyn;

	case R_PPC_REL32:
	  if (h == NULL
	      && got2 != NULL
	      && (sec->flags & SEC_CODE) != 0
	      && (info->shared || info->pie)
	      && htab->plt_type == PLT_UNSET)
	    {
	      /* Old -fPIC gcc code has .long LCTOC1-LCFx just before
		 the start of a function, which assembles to a REL32
		 reference to .got2.  If we detect one of these, then
		 force the old PLT layout because the linker cannot
		 reliably deduce the GOT pointer value needed for
		 PLT call stubs.  */
	      asection *s;

	      s = bfd_section_from_r_symndx (abfd, &htab->sym_sec, sec,
					     r_symndx);
	      if (s == got2)
		{
		  htab->plt_type = PLT_OLD;
		  htab->old_bfd = abfd;
		}
	    }
	  if (h == NULL || h == htab->elf.hgot)
	    break;
	  goto dodyn1;

	case R_PPC_REL24:
	case R_PPC_REL14:
	case R_PPC_REL14_BRTAKEN:
	case R_PPC_REL14_BRNTAKEN:
	  if (h == NULL)
	    break;
	  if (h == htab->elf.hgot)
	    {
	      if (htab->plt_type == PLT_UNSET)
		{
		  htab->plt_type = PLT_OLD;
		  htab->old_bfd = abfd;
		}
	      break;
	    }
	  /* fall through */

	case R_PPC_ADDR32:
	case R_PPC_ADDR24:
	case R_PPC_ADDR16:
	case R_PPC_ADDR16_LO:
	case R_PPC_ADDR16_HI:
	case R_PPC_ADDR16_HA:
	case R_PPC_ADDR14:
	case R_PPC_ADDR14_BRTAKEN:
	case R_PPC_ADDR14_BRNTAKEN:
	case R_PPC_UADDR32:
	case R_PPC_UADDR16:
	dodyn1:
	  if (h != NULL && !info->shared)
	    {
	      /* We may need a plt entry if the symbol turns out to be
		 a function defined in a dynamic object.  */
	      if (!update_plt_info (abfd, h, NULL, 0))
		return FALSE;

	      /* We may need a copy reloc too.  */
	      h->non_got_ref = 1;
	    }

	dodyn:
	  /* If we are creating a shared library, and this is a reloc
	     against a global symbol, or a non PC relative reloc
	     against a local symbol, then we need to copy the reloc
	     into the shared library.  However, if we are linking with
	     -Bsymbolic, we do not need to copy a reloc against a
	     global symbol which is defined in an object we are
	     including in the link (i.e., DEF_REGULAR is set).  At
	     this point we have not seen all the input files, so it is
	     possible that DEF_REGULAR is not set now but will be set
	     later (it is never cleared).  In case of a weak definition,
	     DEF_REGULAR may be cleared later by a strong definition in
	     a shared library.  We account for that possibility below by
	     storing information in the dyn_relocs field of the hash
	     table entry.  A similar situation occurs when creating
	     shared libraries and symbol visibility changes render the
	     symbol local.

	     If on the other hand, we are creating an executable, we
	     may need to keep relocations for symbols satisfied by a
	     dynamic library if we manage to avoid copy relocs for the
	     symbol.  */
	  if ((info->shared
	       && (must_be_dyn_reloc (info, r_type)
		   || (h != NULL
		       && (! info->symbolic
			   || h->root.type == bfd_link_hash_defweak
			   || !h->def_regular))))
	      || (ELIMINATE_COPY_RELOCS
		  && !info->shared
		  && h != NULL
		  && (h->root.type == bfd_link_hash_defweak
		      || !h->def_regular)))
	    {
	      struct ppc_elf_dyn_relocs *p;
	      struct ppc_elf_dyn_relocs **head;

#ifdef DEBUG
	      fprintf (stderr,
		       "ppc_elf_check_relocs needs to "
		       "create relocation for %s\n",
		       (h && h->root.root.string
			? h->root.root.string : "<unknown>"));
#endif
	      if (sreloc == NULL)
		{
		  const char *name;

		  name = (bfd_elf_string_from_elf_section
			  (abfd,
			   elf_elfheader (abfd)->e_shstrndx,
			   elf_section_data (sec)->rel_hdr.sh_name));
		  if (name == NULL)
		    return FALSE;

		  BFD_ASSERT (CONST_STRNEQ (name, ".rela")
			      && strcmp (bfd_get_section_name (abfd, sec),
					 name + 5) == 0);

		  if (htab->elf.dynobj == NULL)
		    htab->elf.dynobj = abfd;
		  sreloc = bfd_get_section_by_name (htab->elf.dynobj, name);
		  if (sreloc == NULL)
		    {
		      flagword flags;

		      flags = (SEC_HAS_CONTENTS | SEC_READONLY
			       | SEC_IN_MEMORY | SEC_LINKER_CREATED
			       | SEC_ALLOC | SEC_LOAD);
		      sreloc = bfd_make_section_with_flags (htab->elf.dynobj,
							    name,
							    flags);
		      if (sreloc == NULL
			  || ! bfd_set_section_alignment (htab->elf.dynobj,
							  sreloc, 2))
			return FALSE;
		    }
		  elf_section_data (sec)->sreloc = sreloc;
		}

	      /* If this is a global symbol, we count the number of
		 relocations we need for this symbol.  */
	      if (h != NULL)
		{
		  head = &ppc_elf_hash_entry (h)->dyn_relocs;
		}
	      else
		{
		  /* Track dynamic relocs needed for local syms too.
		     We really need local syms available to do this
		     easily.  Oh well.  */

		  asection *s;
		  void *vpp;

		  s = bfd_section_from_r_symndx (abfd, &htab->sym_sec,
						 sec, r_symndx);
		  if (s == NULL)
		    return FALSE;

		  vpp = &elf_section_data (s)->local_dynrel;
		  head = (struct ppc_elf_dyn_relocs **) vpp;
		}

	      p = *head;
	      if (p == NULL || p->sec != sec)
		{
		  p = bfd_alloc (htab->elf.dynobj, sizeof *p);
		  if (p == NULL)
		    return FALSE;
		  p->next = *head;
		  *head = p;
		  p->sec = sec;
		  p->count = 0;
		  p->pc_count = 0;
		}

	      p->count += 1;
	      if (!must_be_dyn_reloc (info, r_type))
		p->pc_count += 1;
	    }

	  break;
	}
    }

  return TRUE;
}