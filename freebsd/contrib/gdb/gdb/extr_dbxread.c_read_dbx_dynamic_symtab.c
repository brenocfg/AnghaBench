#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct objfile {int /*<<< orphan*/  section_offsets; int /*<<< orphan*/ * obfd; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_14__ {int value; int flags; int address; struct TYPE_14__** sym_ptr_ptr; TYPE_1__* howto; } ;
typedef  TYPE_2__ asymbol ;
struct TYPE_15__ {int vma; } ;
typedef  TYPE_3__ asection ;
typedef  TYPE_2__ arelent ;
struct TYPE_13__ {int type; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BSF_GLOBAL ; 
 int DYNAMIC ; 
 int N_BSS ; 
 int N_DATA ; 
 int N_EXT ; 
 int N_TEXT ; 
 int RELOC_JMP_SLOT ; 
 int /*<<< orphan*/  SECT_OFF_BSS (struct objfile*) ; 
 int /*<<< orphan*/  SECT_OFF_DATA (struct objfile*) ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_DATA ; 
#define  bfd_arch_m68k 129 
#define  bfd_arch_sparc 128 
 int bfd_arch_unknown ; 
 scalar_t__ bfd_asymbol_name (TYPE_2__*) ; 
 long bfd_canonicalize_dynamic_reloc (int /*<<< orphan*/ *,TYPE_2__**,TYPE_2__**) ; 
 long bfd_canonicalize_dynamic_symtab (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int bfd_get_arch (int /*<<< orphan*/ *) ; 
 long bfd_get_dynamic_reloc_upper_bound (int /*<<< orphan*/ *) ; 
 long bfd_get_dynamic_symtab_upper_bound (int /*<<< orphan*/ *) ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 TYPE_3__* bfd_get_section (TYPE_2__*) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ bfd_get_symcount (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_aout_flavour ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  mst_solib_trampoline ; 
 int /*<<< orphan*/  prim_record_minimal_symbol (char*,int,int /*<<< orphan*/ ,struct objfile*) ; 
 int /*<<< orphan*/  record_minimal_symbol (char*,int,int,struct objfile*) ; 
 int /*<<< orphan*/  xfree ; 
 scalar_t__ xmalloc (long) ; 

__attribute__((used)) static void
read_dbx_dynamic_symtab (struct objfile *objfile)
{
  bfd *abfd = objfile->obfd;
  struct cleanup *back_to;
  int counter;
  long dynsym_size;
  long dynsym_count;
  asymbol **dynsyms;
  asymbol **symptr;
  arelent **relptr;
  long dynrel_size;
  long dynrel_count;
  arelent **dynrels;
  CORE_ADDR sym_value;
  char *name;

  /* Check that the symbol file has dynamic symbols that we know about.
     bfd_arch_unknown can happen if we are reading a sun3 symbol file
     on a sun4 host (and vice versa) and bfd is not configured
     --with-target=all.  This would trigger an assertion in bfd/sunos.c,
     so we ignore the dynamic symbols in this case.  */
  if (bfd_get_flavour (abfd) != bfd_target_aout_flavour
      || (bfd_get_file_flags (abfd) & DYNAMIC) == 0
      || bfd_get_arch (abfd) == bfd_arch_unknown)
    return;

  dynsym_size = bfd_get_dynamic_symtab_upper_bound (abfd);
  if (dynsym_size < 0)
    return;

  dynsyms = (asymbol **) xmalloc (dynsym_size);
  back_to = make_cleanup (xfree, dynsyms);

  dynsym_count = bfd_canonicalize_dynamic_symtab (abfd, dynsyms);
  if (dynsym_count < 0)
    {
      do_cleanups (back_to);
      return;
    }

  /* Enter dynamic symbols into the minimal symbol table
     if this is a stripped executable.  */
  if (bfd_get_symcount (abfd) <= 0)
    {
      symptr = dynsyms;
      for (counter = 0; counter < dynsym_count; counter++, symptr++)
	{
	  asymbol *sym = *symptr;
	  asection *sec;
	  int type;

	  sec = bfd_get_section (sym);

	  /* BFD symbols are section relative.  */
	  sym_value = sym->value + sec->vma;

	  if (bfd_get_section_flags (abfd, sec) & SEC_CODE)
	    {
	      sym_value += ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile));
	      type = N_TEXT;
	    }
	  else if (bfd_get_section_flags (abfd, sec) & SEC_DATA)
	    {
	      sym_value += ANOFFSET (objfile->section_offsets, SECT_OFF_DATA (objfile));
	      type = N_DATA;
	    }
	  else if (bfd_get_section_flags (abfd, sec) & SEC_ALLOC)
	    {
	      sym_value += ANOFFSET (objfile->section_offsets, SECT_OFF_BSS (objfile));
	      type = N_BSS;
	    }
	  else
	    continue;

	  if (sym->flags & BSF_GLOBAL)
	    type |= N_EXT;

	  record_minimal_symbol ((char *) bfd_asymbol_name (sym), sym_value,
				 type, objfile);
	}
    }

  /* Symbols from shared libraries have a dynamic relocation entry
     that points to the associated slot in the procedure linkage table.
     We make a mininal symbol table entry with type mst_solib_trampoline
     at the address in the procedure linkage table.  */
  dynrel_size = bfd_get_dynamic_reloc_upper_bound (abfd);
  if (dynrel_size < 0)
    {
      do_cleanups (back_to);
      return;
    }

  dynrels = (arelent **) xmalloc (dynrel_size);
  make_cleanup (xfree, dynrels);

  dynrel_count = bfd_canonicalize_dynamic_reloc (abfd, dynrels, dynsyms);
  if (dynrel_count < 0)
    {
      do_cleanups (back_to);
      return;
    }

  for (counter = 0, relptr = dynrels;
       counter < dynrel_count;
       counter++, relptr++)
    {
      arelent *rel = *relptr;
      CORE_ADDR address =
      rel->address + ANOFFSET (objfile->section_offsets, SECT_OFF_DATA (objfile));

      switch (bfd_get_arch (abfd))
	{
	case bfd_arch_sparc:
	  if (rel->howto->type != RELOC_JMP_SLOT)
	    continue;
	  break;
	case bfd_arch_m68k:
	  /* `16' is the type BFD produces for a jump table relocation.  */
	  if (rel->howto->type != 16)
	    continue;

	  /* Adjust address in the jump table to point to
	     the start of the bsr instruction.  */
	  address -= 2;
	  break;
	default:
	  continue;
	}

      name = (char *) bfd_asymbol_name (*rel->sym_ptr_ptr);
      prim_record_minimal_symbol (name, address, mst_solib_trampoline,
				  objfile);
    }

  do_cleanups (back_to);
}