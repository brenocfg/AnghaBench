#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct stab_section_info {int num_sections; char* filename; scalar_t__* sections; struct stab_section_info* next; } ;
struct objfile {int /*<<< orphan*/  md; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/  section_offsets; int /*<<< orphan*/  obfd; struct dbx_symfile_info* sym_stab_info; } ;
struct minimal_symbol {char* filename; } ;
struct dbx_symfile_info {struct stab_section_info* stab_section_info; } ;
typedef  enum minimal_symbol_type { ____Placeholder_minimal_symbol_type } minimal_symbol_type ;
struct TYPE_9__ {unsigned short st_shndx; unsigned long st_size; } ;
struct TYPE_10__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;
struct TYPE_11__ {char* name; int flags; scalar_t__ value; TYPE_4__* section; } ;
typedef  TYPE_3__ asymbol ;
struct TYPE_12__ {scalar_t__ vma; int flags; int /*<<< orphan*/  index; } ;
typedef  unsigned long MSYMBOL_SIZE ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BSF_FILE ; 
 int BSF_FUNCTION ; 
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  ELF_MAKE_MSYMBOL_SPECIAL (TYPE_3__*,struct minimal_symbol*) ; 
 int SECT_OFF_BSS (struct objfile*) ; 
 int SECT_OFF_DATA (struct objfile*) ; 
 int SECT_OFF_RODATA (struct objfile*) ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_LOAD ; 
#define  SHN_MIPS_ACOMMON 130 
#define  SHN_MIPS_DATA 129 
#define  SHN_MIPS_TEXT 128 
 TYPE_4__ bfd_abs_section ; 
 scalar_t__ bfd_get_symcount (int /*<<< orphan*/ ) ; 
 TYPE_4__ bfd_und_section ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,char*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memset (struct stab_section_info*,int /*<<< orphan*/ ,size_t) ; 
 int mst_abs ; 
 int mst_bss ; 
 int mst_data ; 
 int mst_file_bss ; 
 int mst_file_data ; 
 int mst_file_text ; 
 int mst_solib_trampoline ; 
 int mst_text ; 
 int mst_unknown ; 
 char* obsavestring (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct minimal_symbol* record_minimal_symbol (char*,scalar_t__,int,TYPE_4__*,struct objfile*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 scalar_t__ xmmalloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
elf_symtab_read (struct objfile *objfile, int dynamic,
		 long number_of_symbols, asymbol **symbol_table)
{
  long storage_needed;
  asymbol *sym;
  long i;
  CORE_ADDR symaddr;
  CORE_ADDR offset;
  enum minimal_symbol_type ms_type;
  /* If sectinfo is nonNULL, it contains section info that should end up
     filed in the objfile.  */
  struct stab_section_info *sectinfo = NULL;
  /* If filesym is nonzero, it points to a file symbol, but we haven't
     seen any section info for it yet.  */
  asymbol *filesym = 0;
#ifdef SOFUN_ADDRESS_MAYBE_MISSING
  /* Name of filesym, as saved on the objfile_obstack.  */
  char *filesymname = obsavestring ("", 0, &objfile->objfile_obstack);
#endif
  struct dbx_symfile_info *dbx = objfile->sym_stab_info;
  int stripped = (bfd_get_symcount (objfile->obfd) == 0);

  if (1)
    {
      for (i = 0; i < number_of_symbols; i++)
	{
	  sym = symbol_table[i];
	  if (sym->name == NULL || *sym->name == '\0')
	    {
	      /* Skip names that don't exist (shouldn't happen), or names
	         that are null strings (may happen). */
	      continue;
	    }

          offset = ANOFFSET (objfile->section_offsets, sym->section->index);
	  if (dynamic
	      && sym->section == &bfd_und_section
	      && (sym->flags & BSF_FUNCTION))
	    {
	      struct minimal_symbol *msym;

	      /* Symbol is a reference to a function defined in
	         a shared library.
	         If its value is non zero then it is usually the address
	         of the corresponding entry in the procedure linkage table,
	         plus the desired section offset.
	         If its value is zero then the dynamic linker has to resolve
	         the symbol. We are unable to find any meaningful address
	         for this symbol in the executable file, so we skip it.  */
	      symaddr = sym->value;
	      if (symaddr == 0)
		continue;
	      symaddr += offset;
	      msym = record_minimal_symbol
		((char *) sym->name, symaddr,
		 mst_solib_trampoline, sym->section, objfile);
#ifdef SOFUN_ADDRESS_MAYBE_MISSING
	      if (msym != NULL)
		msym->filename = filesymname;
#endif
	      continue;
	    }

	  /* If it is a nonstripped executable, do not enter dynamic
	     symbols, as the dynamic symbol table is usually a subset
	     of the main symbol table.  */
	  if (dynamic && !stripped)
	    continue;
	  if (sym->flags & BSF_FILE)
	    {
	      /* STT_FILE debugging symbol that helps stabs-in-elf debugging.
	         Chain any old one onto the objfile; remember new sym.  */
	      if (sectinfo != NULL)
		{
		  sectinfo->next = dbx->stab_section_info;
		  dbx->stab_section_info = sectinfo;
		  sectinfo = NULL;
		}
	      filesym = sym;
#ifdef SOFUN_ADDRESS_MAYBE_MISSING
	      filesymname =
		obsavestring ((char *) filesym->name, strlen (filesym->name),
			      &objfile->objfile_obstack);
#endif
	    }
	  else if (sym->flags & (BSF_GLOBAL | BSF_LOCAL | BSF_WEAK))
	    {
	      struct minimal_symbol *msym;

	      /* Select global/local/weak symbols.  Note that bfd puts abs
	         symbols in their own section, so all symbols we are
	         interested in will have a section. */
	      /* Bfd symbols are section relative. */
	      symaddr = sym->value + sym->section->vma;
	      /* Relocate all non-absolute symbols by the section offset.  */
	      if (sym->section != &bfd_abs_section)
		{
		  symaddr += offset;
		}
	      /* For non-absolute symbols, use the type of the section
	         they are relative to, to intuit text/data.  Bfd provides
	         no way of figuring this out for absolute symbols. */
	      if (sym->section == &bfd_abs_section)
		{
		  /* This is a hack to get the minimal symbol type
		     right for Irix 5, which has absolute addresses
		     with special section indices for dynamic symbols. */
		  unsigned short shndx =
		  ((elf_symbol_type *) sym)->internal_elf_sym.st_shndx;

		  switch (shndx)
		    {
		    case SHN_MIPS_TEXT:
		      ms_type = mst_text;
		      break;
		    case SHN_MIPS_DATA:
		      ms_type = mst_data;
		      break;
		    case SHN_MIPS_ACOMMON:
		      ms_type = mst_bss;
		      break;
		    default:
		      ms_type = mst_abs;
		    }

		  /* If it is an Irix dynamic symbol, skip section name
		     symbols, relocate all others by section offset. */
		  if (ms_type != mst_abs)
		    {
		      if (sym->name[0] == '.')
			continue;
		      symaddr += offset;
		    }
		}
	      else if (sym->section->flags & SEC_CODE)
		{
		  if (sym->flags & BSF_GLOBAL)
		    {
		      ms_type = mst_text;
		    }
		  else if ((sym->name[0] == '.' && sym->name[1] == 'L')
			   || ((sym->flags & BSF_LOCAL)
			       && sym->name[0] == '$'
			       && sym->name[1] == 'L'))
		    /* Looks like a compiler-generated label.  Skip
		       it.  The assembler should be skipping these (to
		       keep executables small), but apparently with
		       gcc on the (deleted) delta m88k SVR4, it loses.
		       So to have us check too should be harmless (but
		       I encourage people to fix this in the assembler
		       instead of adding checks here).  */
		    continue;
		  else
		    {
		      ms_type = mst_file_text;
		    }
		}
	      else if (sym->section->flags & SEC_ALLOC)
		{
		  if (sym->flags & (BSF_GLOBAL | BSF_WEAK))
		    {
		      if (sym->section->flags & SEC_LOAD)
			{
			  ms_type = mst_data;
			}
		      else
			{
			  ms_type = mst_bss;
			}
		    }
		  else if (sym->flags & BSF_LOCAL)
		    {
		      /* Named Local variable in a Data section.
		         Check its name for stabs-in-elf.  */
		      int special_local_sect;
		      if (strcmp ("Bbss.bss", sym->name) == 0)
			special_local_sect = SECT_OFF_BSS (objfile);
		      else if (strcmp ("Ddata.data", sym->name) == 0)
			special_local_sect = SECT_OFF_DATA (objfile);
		      else if (strcmp ("Drodata.rodata", sym->name) == 0)
			special_local_sect = SECT_OFF_RODATA (objfile);
		      else
			special_local_sect = -1;
		      if (special_local_sect >= 0)
			{
			  /* Found a special local symbol.  Allocate a
			     sectinfo, if needed, and fill it in.  */
			  if (sectinfo == NULL)
			    {
			      int max_index;
			      size_t size;

			      max_index 
				= max (SECT_OFF_BSS (objfile),
				       max (SECT_OFF_DATA (objfile),
					    SECT_OFF_RODATA (objfile)));

                              /* max_index is the largest index we'll
                                 use into this array, so we must
                                 allocate max_index+1 elements for it.
                                 However, 'struct stab_section_info'
                                 already includes one element, so we
                                 need to allocate max_index aadditional
                                 elements.  */
			      size = (sizeof (struct stab_section_info) 
				      + (sizeof (CORE_ADDR)
					 * max_index));
			      sectinfo = (struct stab_section_info *)
				xmmalloc (objfile->md, size);
			      memset (sectinfo, 0, size);
			      sectinfo->num_sections = max_index;
			      if (filesym == NULL)
				{
				  complaint (&symfile_complaints,
					     "elf/stab section information %s without a preceding file symbol",
					     sym->name);
				}
			      else
				{
				  sectinfo->filename =
				    (char *) filesym->name;
				}
			    }
			  if (sectinfo->sections[special_local_sect] != 0)
			    complaint (&symfile_complaints,
				       "duplicated elf/stab section information for %s",
				       sectinfo->filename);
			  /* BFD symbols are section relative.  */
			  symaddr = sym->value + sym->section->vma;
			  /* Relocate non-absolute symbols by the
                             section offset.  */
			  if (sym->section != &bfd_abs_section)
			    symaddr += offset;
			  sectinfo->sections[special_local_sect] = symaddr;
			  /* The special local symbols don't go in the
			     minimal symbol table, so ignore this one.  */
			  continue;
			}
		      /* Not a special stabs-in-elf symbol, do regular
		         symbol processing.  */
		      if (sym->section->flags & SEC_LOAD)
			{
			  ms_type = mst_file_data;
			}
		      else
			{
			  ms_type = mst_file_bss;
			}
		    }
		  else
		    {
		      ms_type = mst_unknown;
		    }
		}
	      else
		{
		  /* FIXME:  Solaris2 shared libraries include lots of
		     odd "absolute" and "undefined" symbols, that play 
		     hob with actions like finding what function the PC
		     is in.  Ignore them if they aren't text, data, or bss.  */
		  /* ms_type = mst_unknown; */
		  continue;	/* Skip this symbol. */
		}
	      msym = record_minimal_symbol
		((char *) sym->name, symaddr,
		 ms_type, sym->section, objfile);
	      if (msym)
	      {
		/* Pass symbol size field in via BFD.  FIXME!!!  */
		unsigned long size = ((elf_symbol_type *) sym)->internal_elf_sym.st_size;
		MSYMBOL_SIZE(msym) = size;
	      }
#ifdef SOFUN_ADDRESS_MAYBE_MISSING
	      if (msym != NULL)
		msym->filename = filesymname;
#endif
	      ELF_MAKE_MSYMBOL_SPECIAL (sym, msym);
	    }
	}
    }
}