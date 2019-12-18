#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct partial_symtab {TYPE_1__* objfile; int /*<<< orphan*/  filename; scalar_t__ number_of_dependencies; scalar_t__ readin; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int /*<<< orphan*/ * obfd; } ;

/* Variables and functions */
 scalar_t__ DBX_STAB_SECTION (TYPE_1__*) ; 
 scalar_t__ LDSYMLEN (struct partial_symtab*) ; 
 int /*<<< orphan*/  dbx_next_symbol_text ; 
 int /*<<< orphan*/  dbx_psymtab_to_symtab_1 (struct partial_symtab*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ info_verbose ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  next_symbol_text_func ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  scan_file_globals (TYPE_1__*) ; 
 scalar_t__ stabs_data ; 
 scalar_t__ symfile_relocate_debug_section (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbx_psymtab_to_symtab (struct partial_symtab *pst)
{
  bfd *sym_bfd;
  struct cleanup *back_to = NULL;

  if (!pst)
    return;

  if (pst->readin)
    {
      fprintf_unfiltered (gdb_stderr, "Psymtab for %s already read in.  Shouldn't happen.\n",
			  pst->filename);
      return;
    }

  if (LDSYMLEN (pst) || pst->number_of_dependencies)
    {
      /* Print the message now, before reading the string table,
         to avoid disconcerting pauses.  */
      if (info_verbose)
	{
	  printf_filtered ("Reading in symbols for %s...", pst->filename);
	  gdb_flush (gdb_stdout);
	}

      sym_bfd = pst->objfile->obfd;

      next_symbol_text_func = dbx_next_symbol_text;

      if (DBX_STAB_SECTION (pst->objfile))
	{
	  stabs_data
	    = symfile_relocate_debug_section (pst->objfile->obfd,
					      DBX_STAB_SECTION (pst->objfile),
					      NULL);
	  if (stabs_data)
	    back_to = make_cleanup (free_current_contents, (void *) &stabs_data);
	}

      dbx_psymtab_to_symtab_1 (pst);

      if (back_to)
	do_cleanups (back_to);

      /* Match with global symbols.  This only needs to be done once,
         after all of the symtabs and dependencies have been read in.   */
      scan_file_globals (pst->objfile);

      /* Finish up the debug error message.  */
      if (info_verbose)
	printf_filtered ("done.\n");
    }
}