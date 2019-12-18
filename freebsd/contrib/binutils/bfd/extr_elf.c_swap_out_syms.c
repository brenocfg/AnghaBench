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
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct elf_backend_data {int (* elf_backend_get_symbol_type ) (TYPE_8__*,int) ;TYPE_1__* s; scalar_t__ (* elf_backend_name_local_section_symbols ) (int /*<<< orphan*/ *) ;} ;
struct bfd_strtab_hash {int dummy; } ;
typedef  int flagword ;
struct TYPE_26__ {int st_value; int st_size; int st_shndx; scalar_t__ st_other; } ;
struct TYPE_21__ {TYPE_8__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;
typedef  int bfd_vma ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_22__ {int value; int flags; char* name; TYPE_4__* section; } ;
typedef  TYPE_3__ asymbol ;
struct TYPE_23__ {int flags; int /*<<< orphan*/  name; scalar_t__ vma; struct TYPE_23__* output_section; scalar_t__ output_offset; } ;
typedef  TYPE_4__ asection ;
struct TYPE_25__ {int sh_entsize; int sh_size; int sh_addralign; scalar_t__ sh_name; scalar_t__ sh_info; scalar_t__ sh_link; scalar_t__ sh_addr; scalar_t__ sh_flags; void* sh_type; int /*<<< orphan*/ * contents; } ;
struct TYPE_24__ {unsigned long st_name; int st_value; int st_size; int st_shndx; scalar_t__ st_other; void* st_info; } ;
struct TYPE_20__ {int sizeof_sym; int log_file_align; int /*<<< orphan*/  (* swap_symbol_out ) (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_19__ {int strtab_section; int shstrtab_section; int symtab_shndx_section; TYPE_6__ symtab_shndx_hdr; TYPE_6__ strtab_hdr; TYPE_6__ symtab_hdr; } ;
typedef  TYPE_5__ Elf_Internal_Sym ;
typedef  TYPE_6__ Elf_Internal_Shdr ;
typedef  int /*<<< orphan*/  Elf_External_Sym_Shndx ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int BSF_FILE ; 
 int BSF_FUNCTION ; 
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 int BSF_OBJECT ; 
 int BSF_RELC ; 
 int BSF_SECTION_SYM ; 
 int BSF_SRELC ; 
 int BSF_THREAD_LOCAL ; 
 int BSF_WEAK ; 
 void* ELF_ST_INFO (int,int) ; 
 int FALSE ; 
#define  MAP_DYNSYMTAB 132 
#define  MAP_ONESYMTAB 131 
#define  MAP_SHSTRTAB 130 
#define  MAP_STRTAB 129 
#define  MAP_SYM_SHNDX 128 
 int SEC_THREAD_LOCAL ; 
 int SHN_UNDEF ; 
 void* SHT_STRTAB ; 
 void* SHT_SYMTAB ; 
 void* SHT_SYMTAB_SHNDX ; 
 int STB_GLOBAL ; 
 int STB_LOCAL ; 
 int STB_WEAK ; 
 int STT_FILE ; 
 int STT_FUNC ; 
 int STT_NOTYPE ; 
 int STT_OBJECT ; 
 int STT_RELC ; 
 int STT_SECTION ; 
 int STT_SRELC ; 
 int STT_TLS ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* _bfd_elf_section_from_bfd_section (int /*<<< orphan*/ *,TYPE_4__*) ; 
 struct bfd_strtab_hash* _bfd_elf_stringtab_init () ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _bfd_stringtab_add (struct bfd_strtab_hash*,char*,int,int) ; 
 int /*<<< orphan*/  _bfd_stringtab_free (struct bfd_strtab_hash*) ; 
 int _bfd_stringtab_size (struct bfd_strtab_hash*) ; 
 int /*<<< orphan*/ * bfd_alloc2 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 TYPE_3__** bfd_get_outsymbols (int /*<<< orphan*/ *) ; 
 TYPE_4__* bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bfd_get_symcount (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_is_abs_section (TYPE_4__*) ; 
 scalar_t__ bfd_is_com_section (TYPE_4__*) ; 
 scalar_t__ bfd_is_und_section (TYPE_4__*) ; 
 int bfd_log2 (int) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_zalloc2 (int /*<<< orphan*/ *,int,int) ; 
 int elf_dynsymtab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_map_symbols (int /*<<< orphan*/ *) ; 
 scalar_t__ elf_num_locals (int /*<<< orphan*/ *) ; 
 int elf_onesymtab (int /*<<< orphan*/ *) ; 
 TYPE_2__* elf_symbol_from (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_10__* elf_tdata (int /*<<< orphan*/ *) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *) ; 
 int stub3 (TYPE_8__*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
swap_out_syms (bfd *abfd,
	       struct bfd_strtab_hash **sttp,
	       int relocatable_p)
{
  const struct elf_backend_data *bed;
  int symcount;
  asymbol **syms;
  struct bfd_strtab_hash *stt;
  Elf_Internal_Shdr *symtab_hdr;
  Elf_Internal_Shdr *symtab_shndx_hdr;
  Elf_Internal_Shdr *symstrtab_hdr;
  bfd_byte *outbound_syms;
  bfd_byte *outbound_shndx;
  int idx;
  bfd_size_type amt;
  bfd_boolean name_local_sections;

  if (!elf_map_symbols (abfd))
    return FALSE;

  /* Dump out the symtabs.  */
  stt = _bfd_elf_stringtab_init ();
  if (stt == NULL)
    return FALSE;

  bed = get_elf_backend_data (abfd);
  symcount = bfd_get_symcount (abfd);
  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  symtab_hdr->sh_type = SHT_SYMTAB;
  symtab_hdr->sh_entsize = bed->s->sizeof_sym;
  symtab_hdr->sh_size = symtab_hdr->sh_entsize * (symcount + 1);
  symtab_hdr->sh_info = elf_num_locals (abfd) + 1;
  symtab_hdr->sh_addralign = 1 << bed->s->log_file_align;

  symstrtab_hdr = &elf_tdata (abfd)->strtab_hdr;
  symstrtab_hdr->sh_type = SHT_STRTAB;

  outbound_syms = bfd_alloc2 (abfd, 1 + symcount, bed->s->sizeof_sym);
  if (outbound_syms == NULL)
    {
      _bfd_stringtab_free (stt);
      return FALSE;
    }
  symtab_hdr->contents = outbound_syms;

  outbound_shndx = NULL;
  symtab_shndx_hdr = &elf_tdata (abfd)->symtab_shndx_hdr;
  if (symtab_shndx_hdr->sh_name != 0)
    {
      amt = (bfd_size_type) (1 + symcount) * sizeof (Elf_External_Sym_Shndx);
      outbound_shndx = bfd_zalloc2 (abfd, 1 + symcount,
				    sizeof (Elf_External_Sym_Shndx));
      if (outbound_shndx == NULL)
	{
	  _bfd_stringtab_free (stt);
	  return FALSE;
	}

      symtab_shndx_hdr->contents = outbound_shndx;
      symtab_shndx_hdr->sh_type = SHT_SYMTAB_SHNDX;
      symtab_shndx_hdr->sh_size = amt;
      symtab_shndx_hdr->sh_addralign = sizeof (Elf_External_Sym_Shndx);
      symtab_shndx_hdr->sh_entsize = sizeof (Elf_External_Sym_Shndx);
    }

  /* Now generate the data (for "contents").  */
  {
    /* Fill in zeroth symbol and swap it out.  */
    Elf_Internal_Sym sym;
    sym.st_name = 0;
    sym.st_value = 0;
    sym.st_size = 0;
    sym.st_info = 0;
    sym.st_other = 0;
    sym.st_shndx = SHN_UNDEF;
    bed->s->swap_symbol_out (abfd, &sym, outbound_syms, outbound_shndx);
    outbound_syms += bed->s->sizeof_sym;
    if (outbound_shndx != NULL)
      outbound_shndx += sizeof (Elf_External_Sym_Shndx);
  }

  name_local_sections
    = (bed->elf_backend_name_local_section_symbols
       && bed->elf_backend_name_local_section_symbols (abfd));

  syms = bfd_get_outsymbols (abfd);
  for (idx = 0; idx < symcount; idx++)
    {
      Elf_Internal_Sym sym;
      bfd_vma value = syms[idx]->value;
      elf_symbol_type *type_ptr;
      flagword flags = syms[idx]->flags;
      int type;

      if (!name_local_sections
	  && (flags & (BSF_SECTION_SYM | BSF_GLOBAL)) == BSF_SECTION_SYM)
	{
	  /* Local section symbols have no name.  */
	  sym.st_name = 0;
	}
      else
	{
	  sym.st_name = (unsigned long) _bfd_stringtab_add (stt,
							    syms[idx]->name,
							    TRUE, FALSE);
	  if (sym.st_name == (unsigned long) -1)
	    {
	      _bfd_stringtab_free (stt);
	      return FALSE;
	    }
	}

      type_ptr = elf_symbol_from (abfd, syms[idx]);

      if ((flags & BSF_SECTION_SYM) == 0
	  && bfd_is_com_section (syms[idx]->section))
	{
	  /* ELF common symbols put the alignment into the `value' field,
	     and the size into the `size' field.  This is backwards from
	     how BFD handles it, so reverse it here.  */
	  sym.st_size = value;
	  if (type_ptr == NULL
	      || type_ptr->internal_elf_sym.st_value == 0)
	    sym.st_value = value >= 16 ? 16 : (1 << bfd_log2 (value));
	  else
	    sym.st_value = type_ptr->internal_elf_sym.st_value;
	  sym.st_shndx = _bfd_elf_section_from_bfd_section
	    (abfd, syms[idx]->section);
	}
      else
	{
	  asection *sec = syms[idx]->section;
	  int shndx;

	  if (sec->output_section)
	    {
	      value += sec->output_offset;
	      sec = sec->output_section;
	    }

	  /* Don't add in the section vma for relocatable output.  */
	  if (! relocatable_p)
	    value += sec->vma;
	  sym.st_value = value;
	  sym.st_size = type_ptr ? type_ptr->internal_elf_sym.st_size : 0;

	  if (bfd_is_abs_section (sec)
	      && type_ptr != NULL
	      && type_ptr->internal_elf_sym.st_shndx != 0)
	    {
	      /* This symbol is in a real ELF section which we did
		 not create as a BFD section.  Undo the mapping done
		 by copy_private_symbol_data.  */
	      shndx = type_ptr->internal_elf_sym.st_shndx;
	      switch (shndx)
		{
		case MAP_ONESYMTAB:
		  shndx = elf_onesymtab (abfd);
		  break;
		case MAP_DYNSYMTAB:
		  shndx = elf_dynsymtab (abfd);
		  break;
		case MAP_STRTAB:
		  shndx = elf_tdata (abfd)->strtab_section;
		  break;
		case MAP_SHSTRTAB:
		  shndx = elf_tdata (abfd)->shstrtab_section;
		  break;
		case MAP_SYM_SHNDX:
		  shndx = elf_tdata (abfd)->symtab_shndx_section;
		  break;
		default:
		  break;
		}
	    }
	  else
	    {
	      shndx = _bfd_elf_section_from_bfd_section (abfd, sec);

	      if (shndx == -1)
		{
		  asection *sec2;

		  /* Writing this would be a hell of a lot easier if
		     we had some decent documentation on bfd, and
		     knew what to expect of the library, and what to
		     demand of applications.  For example, it
		     appears that `objcopy' might not set the
		     section of a symbol to be a section that is
		     actually in the output file.  */
		  sec2 = bfd_get_section_by_name (abfd, sec->name);
		  if (sec2 == NULL)
		    {
		      _bfd_error_handler (_("\
Unable to find equivalent output section for symbol '%s' from section '%s'"),
					  syms[idx]->name ? syms[idx]->name : "<Local sym>",
					  sec->name);
		      bfd_set_error (bfd_error_invalid_operation);
		      _bfd_stringtab_free (stt);
		      return FALSE;
		    }

		  shndx = _bfd_elf_section_from_bfd_section (abfd, sec2);
		  BFD_ASSERT (shndx != -1);
		}
	    }

	  sym.st_shndx = shndx;
	}

      if ((flags & BSF_THREAD_LOCAL) != 0)
	type = STT_TLS;
      else if ((flags & BSF_FUNCTION) != 0)
	type = STT_FUNC;
      else if ((flags & BSF_OBJECT) != 0)
	type = STT_OBJECT;
      else if ((flags & BSF_RELC) != 0)
	type = STT_RELC;
      else if ((flags & BSF_SRELC) != 0)
	type = STT_SRELC;
      else
	type = STT_NOTYPE;

      if (syms[idx]->section->flags & SEC_THREAD_LOCAL)
	type = STT_TLS;

      /* Processor-specific types.  */
      if (type_ptr != NULL
	  && bed->elf_backend_get_symbol_type)
	type = ((*bed->elf_backend_get_symbol_type)
		(&type_ptr->internal_elf_sym, type));

      if (flags & BSF_SECTION_SYM)
	{
	  if (flags & BSF_GLOBAL)
	    sym.st_info = ELF_ST_INFO (STB_GLOBAL, STT_SECTION);
	  else
	    sym.st_info = ELF_ST_INFO (STB_LOCAL, STT_SECTION);
	}
      else if (bfd_is_com_section (syms[idx]->section))
	sym.st_info = ELF_ST_INFO (STB_GLOBAL, type);
      else if (bfd_is_und_section (syms[idx]->section))
	sym.st_info = ELF_ST_INFO (((flags & BSF_WEAK)
				    ? STB_WEAK
				    : STB_GLOBAL),
				   type);
      else if (flags & BSF_FILE)
	sym.st_info = ELF_ST_INFO (STB_LOCAL, STT_FILE);
      else
	{
	  int bind = STB_LOCAL;

	  if (flags & BSF_LOCAL)
	    bind = STB_LOCAL;
	  else if (flags & BSF_WEAK)
	    bind = STB_WEAK;
	  else if (flags & BSF_GLOBAL)
	    bind = STB_GLOBAL;

	  sym.st_info = ELF_ST_INFO (bind, type);
	}

      if (type_ptr != NULL)
	sym.st_other = type_ptr->internal_elf_sym.st_other;
      else
	sym.st_other = 0;

      bed->s->swap_symbol_out (abfd, &sym, outbound_syms, outbound_shndx);
      outbound_syms += bed->s->sizeof_sym;
      if (outbound_shndx != NULL)
	outbound_shndx += sizeof (Elf_External_Sym_Shndx);
    }

  *sttp = stt;
  symstrtab_hdr->sh_size = _bfd_stringtab_size (stt);
  symstrtab_hdr->sh_type = SHT_STRTAB;

  symstrtab_hdr->sh_flags = 0;
  symstrtab_hdr->sh_addr = 0;
  symstrtab_hdr->sh_entsize = 0;
  symstrtab_hdr->sh_link = 0;
  symstrtab_hdr->sh_info = 0;
  symstrtab_hdr->sh_addralign = 1;

  return TRUE;
}