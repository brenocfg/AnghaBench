#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int bfd_boolean ;
struct TYPE_24__ {int flags; TYPE_1__* xvec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_23__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HAS_RELOC ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  adjust_addresses ; 
 scalar_t__ adjust_section_vma ; 
 int /*<<< orphan*/  bfd_demangle ; 
 scalar_t__ bfd_get_dynamic_symtab_upper_bound (TYPE_2__*) ; 
 char* bfd_get_filename (TYPE_2__*) ; 
 scalar_t__ bfd_get_synthetic_symtab (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bfd_map_over_sections (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ disassemble ; 
 int /*<<< orphan*/  disassemble_data (TYPE_2__*) ; 
 scalar_t__ dump_ar_hdrs ; 
 int /*<<< orphan*/  dump_bfd_header (TYPE_2__*) ; 
 int /*<<< orphan*/  dump_bfd_private_header (TYPE_2__*) ; 
 int /*<<< orphan*/  dump_data (TYPE_2__*) ; 
 scalar_t__ dump_debugging ; 
 scalar_t__ dump_debugging_tags ; 
 int /*<<< orphan*/  dump_dwarf (TYPE_2__*) ; 
 scalar_t__ dump_dwarf_section_info ; 
 scalar_t__ dump_dynamic_reloc_info ; 
 int /*<<< orphan*/  dump_dynamic_relocs (TYPE_2__*) ; 
 scalar_t__ dump_dynamic_symtab ; 
 scalar_t__ dump_file_header ; 
 int /*<<< orphan*/  dump_headers (TYPE_2__*) ; 
 scalar_t__ dump_private_headers ; 
 scalar_t__ dump_reloc_info ; 
 int /*<<< orphan*/  dump_relocs (TYPE_2__*) ; 
 scalar_t__ dump_section_contents ; 
 scalar_t__ dump_section_headers ; 
 scalar_t__ dump_stab_section_info ; 
 int /*<<< orphan*/  dump_stabs (TYPE_2__*) ; 
 int /*<<< orphan*/  dump_symbols (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dump_symtab ; 
 scalar_t__ dynsymcount ; 
 int /*<<< orphan*/ * dynsyms ; 
 int exit_status ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  non_fatal (char*,char*) ; 
 int /*<<< orphan*/  print_arelt_descr (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_debugging_info (int /*<<< orphan*/ ,void*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 void* read_debugging_info (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * slurp_dynamic_symtab (TYPE_2__*) ; 
 int /*<<< orphan*/ * slurp_symtab (TYPE_2__*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ symcount ; 
 int /*<<< orphan*/ * syms ; 
 scalar_t__ synthcount ; 
 int /*<<< orphan*/ * synthsyms ; 

__attribute__((used)) static void
dump_bfd (bfd *abfd)
{
  /* If we are adjusting section VMA's, change them all now.  Changing
     the BFD information is a hack.  However, we must do it, or
     bfd_find_nearest_line will not do the right thing.  */
  if (adjust_section_vma != 0)
    {
      bfd_boolean has_reloc = (abfd->flags & HAS_RELOC);
      bfd_map_over_sections (abfd, adjust_addresses, &has_reloc);
    }

  if (! dump_debugging_tags)
    printf (_("\n%s:     file format %s\n"), bfd_get_filename (abfd),
	    abfd->xvec->name);
  if (dump_ar_hdrs)
    print_arelt_descr (stdout, abfd, TRUE);
  if (dump_file_header)
    dump_bfd_header (abfd);
  if (dump_private_headers)
    dump_bfd_private_header (abfd);
  if (! dump_debugging_tags)
    putchar ('\n');
  if (dump_section_headers)
    dump_headers (abfd);

  if (dump_symtab
      || dump_reloc_info
      || disassemble
      || dump_debugging
      || dump_dwarf_section_info)
    syms = slurp_symtab (abfd);
  if (dump_dynamic_symtab || dump_dynamic_reloc_info
      || (disassemble && bfd_get_dynamic_symtab_upper_bound (abfd) > 0))
    dynsyms = slurp_dynamic_symtab (abfd);
  if (disassemble)
    {
      synthcount = bfd_get_synthetic_symtab (abfd, symcount, syms,
					     dynsymcount, dynsyms, &synthsyms);
      if (synthcount < 0)
	synthcount = 0;
    }

  if (dump_symtab)
    dump_symbols (abfd, FALSE);
  if (dump_dynamic_symtab)
    dump_symbols (abfd, TRUE);
  if (dump_dwarf_section_info)
    dump_dwarf (abfd);
  if (dump_stab_section_info)
    dump_stabs (abfd);
  if (dump_reloc_info && ! disassemble)
    dump_relocs (abfd);
  if (dump_dynamic_reloc_info && ! disassemble)
    dump_dynamic_relocs (abfd);
  if (dump_section_contents)
    dump_data (abfd);
  if (disassemble)
    disassemble_data (abfd);

  if (dump_debugging)
    {
      void *dhandle;

      dhandle = read_debugging_info (abfd, syms, symcount);
      if (dhandle != NULL)
	{
	  if (!print_debugging_info (stdout, dhandle, abfd, syms,
				     bfd_demangle,
				     dump_debugging_tags ? TRUE : FALSE))
	    {
	      non_fatal (_("%s: printing debugging information failed"),
			 bfd_get_filename (abfd));
	      exit_status = 1;
	    }
	}
    }

  if (syms)
    {
      free (syms);
      syms = NULL;
    }

  if (dynsyms)
    {
      free (dynsyms);
      dynsyms = NULL;
    }

  if (synthsyms)
    {
      free (synthsyms);
      synthsyms = NULL;
    }

  symcount = 0;
  dynsymcount = 0;
  synthcount = 0;
}