#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_20__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_14__ ;
typedef  struct TYPE_38__   TYPE_10__ ;

/* Type definitions */
struct elf_backend_data {int /*<<< orphan*/  (* elf_backend_symbol_table_processing ) (TYPE_2__*,TYPE_1__*,unsigned long) ;int /*<<< orphan*/  (* elf_backend_symbol_processing ) (TYPE_2__*,TYPE_10__*) ;} ;
struct TYPE_38__ {int flags; TYPE_20__* section; int /*<<< orphan*/  value; int /*<<< orphan*/  name; TYPE_2__* the_bfd; } ;
struct TYPE_40__ {TYPE_10__ symbol; int /*<<< orphan*/  version; int /*<<< orphan*/  internal_elf_sym; } ;
typedef  TYPE_1__ elf_symbol_type ;
typedef  int bfd_size_type ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_42__ {int flags; int /*<<< orphan*/  filename; } ;
typedef  TYPE_2__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_45__ {int sh_size; unsigned char* contents; int /*<<< orphan*/  sh_offset; } ;
struct TYPE_44__ {scalar_t__ st_shndx; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_value; } ;
struct TYPE_43__ {int /*<<< orphan*/  vs_vers; } ;
struct TYPE_41__ {scalar_t__ vma; } ;
struct TYPE_39__ {scalar_t__ dynverdef_section; scalar_t__ dynverref_section; int /*<<< orphan*/ * verref; int /*<<< orphan*/ * verdef; TYPE_5__ dynversym_hdr; TYPE_5__ dynsymtab_hdr; TYPE_5__ symtab_hdr; } ;
typedef  TYPE_3__ Elf_Internal_Versym ;
typedef  TYPE_4__ Elf_Internal_Sym ;
typedef  TYPE_5__ Elf_Internal_Shdr ;
typedef  TYPE_4__ Elf_External_Versym ;
typedef  int /*<<< orphan*/  Elf_External_Sym ;

/* Variables and functions */
 int BSF_DEBUGGING ; 
 int BSF_DYNAMIC ; 
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
 int DYNAMIC ; 
 int ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int EXEC_P ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SHN_ABS ; 
 scalar_t__ SHN_COMMON ; 
 scalar_t__ SHN_HIRESERVE ; 
 scalar_t__ SHN_LORESERVE ; 
 scalar_t__ SHN_UNDEF ; 
#define  STB_GLOBAL 137 
#define  STB_LOCAL 136 
#define  STB_WEAK 135 
#define  STT_FILE 134 
#define  STT_FUNC 133 
#define  STT_OBJECT 132 
#define  STT_RELC 131 
#define  STT_SECTION 130 
#define  STT_SRELC 129 
#define  STT_TLS 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_slurp_version_tables (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bfd_elf_swap_versym_in (TYPE_2__*,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,unsigned long) ; 
 void* bfd_abs_section_ptr ; 
 int bfd_bread (TYPE_4__*,int,TYPE_2__*) ; 
 TYPE_20__* bfd_com_section_ptr ; 
 TYPE_4__* bfd_elf_get_elf_syms (TYPE_2__*,TYPE_5__*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_elf_sym_name (TYPE_2__*,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* bfd_malloc (int) ; 
 TYPE_20__* bfd_section_from_elf_index (TYPE_2__*,scalar_t__) ; 
 scalar_t__ bfd_seek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_20__* bfd_und_section_ptr ; 
 TYPE_1__* bfd_zalloc (TYPE_2__*,int) ; 
 scalar_t__ elf_dynversym (TYPE_2__*) ; 
 TYPE_14__* elf_tdata (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 struct elf_backend_data* get_elf_backend_data (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,unsigned long) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_10__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,TYPE_1__*,unsigned long) ; 

long
elf_slurp_symbol_table (bfd *abfd, asymbol **symptrs, bfd_boolean dynamic)
{
  Elf_Internal_Shdr *hdr;
  Elf_Internal_Shdr *verhdr;
  unsigned long symcount;	/* Number of external ELF symbols */
  elf_symbol_type *sym;		/* Pointer to current bfd symbol */
  elf_symbol_type *symbase;	/* Buffer for generated bfd symbols */
  Elf_Internal_Sym *isym;
  Elf_Internal_Sym *isymend;
  Elf_Internal_Sym *isymbuf = NULL;
  Elf_External_Versym *xver;
  Elf_External_Versym *xverbuf = NULL;
  const struct elf_backend_data *ebd;
  bfd_size_type amt;

  /* Read each raw ELF symbol, converting from external ELF form to
     internal ELF form, and then using the information to create a
     canonical bfd symbol table entry.

     Note that we allocate the initial bfd canonical symbol buffer
     based on a one-to-one mapping of the ELF symbols to canonical
     symbols.  We actually use all the ELF symbols, so there will be no
     space left over at the end.  When we have all the symbols, we
     build the caller's pointer vector.  */

  if (! dynamic)
    {
      hdr = &elf_tdata (abfd)->symtab_hdr;
      verhdr = NULL;
    }
  else
    {
      hdr = &elf_tdata (abfd)->dynsymtab_hdr;
      if (elf_dynversym (abfd) == 0)
	verhdr = NULL;
      else
	verhdr = &elf_tdata (abfd)->dynversym_hdr;
      if ((elf_tdata (abfd)->dynverdef_section != 0
	   && elf_tdata (abfd)->verdef == NULL)
	  || (elf_tdata (abfd)->dynverref_section != 0
	      && elf_tdata (abfd)->verref == NULL))
	{
	  if (!_bfd_elf_slurp_version_tables (abfd, FALSE))
	    return -1;
	}
    }

  ebd = get_elf_backend_data (abfd);
  symcount = hdr->sh_size / sizeof (Elf_External_Sym);
  if (symcount == 0)
    sym = symbase = NULL;
  else
    {
      isymbuf = bfd_elf_get_elf_syms (abfd, hdr, symcount, 0,
				      NULL, NULL, NULL);
      if (isymbuf == NULL)
	return -1;

      amt = symcount;
      amt *= sizeof (elf_symbol_type);
      symbase = bfd_zalloc (abfd, amt);
      if (symbase == (elf_symbol_type *) NULL)
	goto error_return;

      /* Read the raw ELF version symbol information.  */
      if (verhdr != NULL
	  && verhdr->sh_size / sizeof (Elf_External_Versym) != symcount)
	{
	  (*_bfd_error_handler)
	    (_("%s: version count (%ld) does not match symbol count (%ld)"),
	     abfd->filename,
	     (long) (verhdr->sh_size / sizeof (Elf_External_Versym)),
	     symcount);

	  /* Slurp in the symbols without the version information,
	     since that is more helpful than just quitting.  */
	  verhdr = NULL;
	}

      if (verhdr != NULL)
	{
	  if (bfd_seek (abfd, verhdr->sh_offset, SEEK_SET) != 0)
	    goto error_return;

	  xverbuf = bfd_malloc (verhdr->sh_size);
	  if (xverbuf == NULL && verhdr->sh_size != 0)
	    goto error_return;

	  if (bfd_bread (xverbuf, verhdr->sh_size, abfd) != verhdr->sh_size)
	    goto error_return;
	}

      /* Skip first symbol, which is a null dummy.  */
      xver = xverbuf;
      if (xver != NULL)
	++xver;
      isymend = isymbuf + symcount;
      for (isym = isymbuf + 1, sym = symbase; isym < isymend; isym++, sym++)
	{
	  memcpy (&sym->internal_elf_sym, isym, sizeof (Elf_Internal_Sym));
	  sym->symbol.the_bfd = abfd;

	  sym->symbol.name = bfd_elf_sym_name (abfd, hdr, isym, NULL);

	  sym->symbol.value = isym->st_value;

	  if (isym->st_shndx == SHN_UNDEF)
	    {
	      sym->symbol.section = bfd_und_section_ptr;
	    }
	  else if (isym->st_shndx < SHN_LORESERVE
		   || isym->st_shndx > SHN_HIRESERVE)
	    {
	      sym->symbol.section = bfd_section_from_elf_index (abfd,
								isym->st_shndx);
	      if (sym->symbol.section == NULL)
		{
		  /* This symbol is in a section for which we did not
		     create a BFD section.  Just use bfd_abs_section,
		     although it is wrong.  FIXME.  */
		  sym->symbol.section = bfd_abs_section_ptr;
		}
	    }
	  else if (isym->st_shndx == SHN_ABS)
	    {
	      sym->symbol.section = bfd_abs_section_ptr;
	    }
	  else if (isym->st_shndx == SHN_COMMON)
	    {
	      sym->symbol.section = bfd_com_section_ptr;
	      /* Elf puts the alignment into the `value' field, and
		 the size into the `size' field.  BFD wants to see the
		 size in the value field, and doesn't care (at the
		 moment) about the alignment.  */
	      sym->symbol.value = isym->st_size;
	    }
	  else
	    sym->symbol.section = bfd_abs_section_ptr;

	  /* If this is a relocatable file, then the symbol value is
	     already section relative.  */
	  if ((abfd->flags & (EXEC_P | DYNAMIC)) != 0)
	    sym->symbol.value -= sym->symbol.section->vma;

	  switch (ELF_ST_BIND (isym->st_info))
	    {
	    case STB_LOCAL:
	      sym->symbol.flags |= BSF_LOCAL;
	      break;
	    case STB_GLOBAL:
	      if (isym->st_shndx != SHN_UNDEF && isym->st_shndx != SHN_COMMON)
		sym->symbol.flags |= BSF_GLOBAL;
	      break;
	    case STB_WEAK:
	      sym->symbol.flags |= BSF_WEAK;
	      break;
	    }

	  switch (ELF_ST_TYPE (isym->st_info))
	    {
	    case STT_SECTION:
	      sym->symbol.flags |= BSF_SECTION_SYM | BSF_DEBUGGING;
	      break;
	    case STT_FILE:
	      sym->symbol.flags |= BSF_FILE | BSF_DEBUGGING;
	      break;
	    case STT_FUNC:
	      sym->symbol.flags |= BSF_FUNCTION;
	      break;
	    case STT_OBJECT:
	      sym->symbol.flags |= BSF_OBJECT;
	      break;
	    case STT_TLS:
	      sym->symbol.flags |= BSF_THREAD_LOCAL;
	      break;
	    case STT_RELC:
	      sym->symbol.flags |= BSF_RELC;
	      break;
	    case STT_SRELC:
	      sym->symbol.flags |= BSF_SRELC;
	      break;
	    }

	  if (dynamic)
	    sym->symbol.flags |= BSF_DYNAMIC;

	  if (xver != NULL)
	    {
	      Elf_Internal_Versym iversym;

	      _bfd_elf_swap_versym_in (abfd, xver, &iversym);
	      sym->version = iversym.vs_vers;
	      xver++;
	    }

	  /* Do some backend-specific processing on this symbol.  */
	  if (ebd->elf_backend_symbol_processing)
	    (*ebd->elf_backend_symbol_processing) (abfd, &sym->symbol);
	}
    }

  /* Do some backend-specific processing on this symbol table.  */
  if (ebd->elf_backend_symbol_table_processing)
    (*ebd->elf_backend_symbol_table_processing) (abfd, symbase, symcount);

  /* We rely on the zalloc to clear out the final symbol entry.  */

  symcount = sym - symbase;

  /* Fill in the user's symbol pointer vector if needed.  */
  if (symptrs)
    {
      long l = symcount;

      sym = symbase;
      while (l-- > 0)
	{
	  *symptrs++ = &sym->symbol;
	  sym++;
	}
      *symptrs = 0;		/* Final null pointer */
    }

  if (xverbuf != NULL)
    free (xverbuf);
  if (isymbuf != NULL && hdr->contents != (unsigned char *) isymbuf)
    free (isymbuf);
  return symcount;

error_return:
  if (xverbuf != NULL)
    free (xverbuf);
  if (isymbuf != NULL && hdr->contents != (unsigned char *) isymbuf)
    free (isymbuf);
  return -1;
}