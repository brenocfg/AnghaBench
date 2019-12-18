#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ entry_point; scalar_t__ deprecated_entry_file_lowpc; void* deprecated_entry_file_highpc; } ;
struct objfile {TYPE_1__ ei; int /*<<< orphan*/  section_offsets; int /*<<< orphan*/ * obfd; } ;
struct minimal_symbol {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_6__ {int /*<<< orphan*/  (* read_debug_info ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_2__ debug_swap; } ;
struct TYPE_7__ {int /*<<< orphan*/  debug_info; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_SYMBOL_NAME (struct minimal_symbol*) ; 
 scalar_t__ INVALID_ENTRY_LOWPC ; 
 scalar_t__ INVALID_ENTRY_POINT ; 
 void* SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 TYPE_4__* ecoff_backend (int /*<<< orphan*/ *) ; 
 TYPE_3__* ecoff_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_minimal_symbol_collection () ; 
 int /*<<< orphan*/  install_minimal_symbols (struct objfile*) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (scalar_t__) ; 
 struct cleanup* make_cleanup_discard_minimal_symbols () ; 
 int /*<<< orphan*/  mdebug_build_psymtabs (struct objfile*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_alphacoff_dynamic_symtab (int /*<<< orphan*/ ,struct objfile*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mipscoff_symfile_read (struct objfile *objfile, int mainline)
{
  bfd *abfd = objfile->obfd;
  struct cleanup *back_to;

  init_minimal_symbol_collection ();
  back_to = make_cleanup_discard_minimal_symbols ();

  /* Now that the executable file is positioned at symbol table,
     process it and define symbols accordingly.  */

  if (!((*ecoff_backend (abfd)->debug_swap.read_debug_info)
	(abfd, (asection *) NULL, &ecoff_data (abfd)->debug_info)))
    error ("Error reading symbol table: %s", bfd_errmsg (bfd_get_error ()));

  mdebug_build_psymtabs (objfile, &ecoff_backend (abfd)->debug_swap,
			 &ecoff_data (abfd)->debug_info);

  /* Add alpha coff dynamic symbols.  */

  read_alphacoff_dynamic_symtab (objfile->section_offsets, objfile);

  /* Install any minimal symbols that have been collected as the current
     minimal symbols for this objfile. */

  install_minimal_symbols (objfile);

  /* If the entry_file bounds are still unknown after processing the
     partial symbols, then try to set them from the minimal symbols
     surrounding the entry_point.  */

  if (mainline
      && objfile->ei.entry_point != INVALID_ENTRY_POINT
      && objfile->ei.deprecated_entry_file_lowpc == INVALID_ENTRY_LOWPC)
    {
      struct minimal_symbol *m;

      m = lookup_minimal_symbol_by_pc (objfile->ei.entry_point);
      if (m && DEPRECATED_SYMBOL_NAME (m + 1))
	{
	  objfile->ei.deprecated_entry_file_lowpc = SYMBOL_VALUE_ADDRESS (m);
	  objfile->ei.deprecated_entry_file_highpc = SYMBOL_VALUE_ADDRESS (m + 1);
	}
    }

  do_cleanups (back_to);
}