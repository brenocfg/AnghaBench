#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; } ;
struct TYPE_3__ {scalar_t__ size; } ;
struct objfile {TYPE_2__ static_psymbols; TYPE_1__ global_psymbols; int /*<<< orphan*/  name; int /*<<< orphan*/ * obfd; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  DBX_SYMBOL_SIZE (struct objfile*) ; 
 int /*<<< orphan*/  DBX_SYMCOUNT (struct objfile*) ; 
 int /*<<< orphan*/  DBX_SYMTAB_OFFSET (struct objfile*) ; 
 int HAS_RELOC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_target (int /*<<< orphan*/ *) ; 
 int bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int block_address_function_relative ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  free_pending_blocks () ; 
 int /*<<< orphan*/  init_minimal_symbol_collection () ; 
 int /*<<< orphan*/  init_psymbol_list (struct objfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_minimal_symbols (struct objfile*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_cleanup_discard_minimal_symbols () ; 
 int /*<<< orphan*/  perror_with_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_dbx_dynamic_symtab (struct objfile*) ; 
 int /*<<< orphan*/  read_dbx_symtab (struct objfile*) ; 
 int /*<<< orphan*/  really_free_pendings ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  symbol_size ; 
 int /*<<< orphan*/  symbol_table_offset ; 
 int symfile_relocatable ; 

__attribute__((used)) static void
dbx_symfile_read (struct objfile *objfile, int mainline)
{
  bfd *sym_bfd;
  int val;
  struct cleanup *back_to;

  sym_bfd = objfile->obfd;

  /* .o and .nlm files are relocatables with text, data and bss segs based at
     0.  This flag disables special (Solaris stabs-in-elf only) fixups for
     symbols with a value of 0.  */

  symfile_relocatable = bfd_get_file_flags (sym_bfd) & HAS_RELOC;

  /* This is true for Solaris (and all other systems which put stabs
     in sections, hopefully, since it would be silly to do things
     differently from Solaris), and false for SunOS4 and other a.out
     file formats.  */
  block_address_function_relative =
    ((0 == strncmp (bfd_get_target (sym_bfd), "elf", 3))
     || (0 == strncmp (bfd_get_target (sym_bfd), "som", 3))
     || (0 == strncmp (bfd_get_target (sym_bfd), "coff", 4))
     || (0 == strncmp (bfd_get_target (sym_bfd), "pe", 2))
     || (0 == strncmp (bfd_get_target (sym_bfd), "epoc-pe", 7))
     || (0 == strncmp (bfd_get_target (sym_bfd), "nlm", 3)));

  val = bfd_seek (sym_bfd, DBX_SYMTAB_OFFSET (objfile), SEEK_SET);
  if (val < 0)
    perror_with_name (objfile->name);

  /* If we are reinitializing, or if we have never loaded syms yet, init */
  if (mainline
      || (objfile->global_psymbols.size == 0
	  &&  objfile->static_psymbols.size == 0))
    init_psymbol_list (objfile, DBX_SYMCOUNT (objfile));

  symbol_size = DBX_SYMBOL_SIZE (objfile);
  symbol_table_offset = DBX_SYMTAB_OFFSET (objfile);

  free_pending_blocks ();
  back_to = make_cleanup (really_free_pendings, 0);

  init_minimal_symbol_collection ();
  make_cleanup_discard_minimal_symbols ();

  /* Read stabs data from executable file and define symbols. */

  read_dbx_symtab (objfile);

  /* Add the dynamic symbols.  */

  read_dbx_dynamic_symtab (objfile);

  /* Install any minimal symbols that have been collected as the current
     minimal symbols for this objfile. */

  install_minimal_symbols (objfile);

  do_cleanups (back_to);
}