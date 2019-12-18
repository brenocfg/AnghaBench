#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct partial_symtab {int /*<<< orphan*/  objfile; int /*<<< orphan*/  filename; scalar_t__ number_of_dependencies; scalar_t__ readin; } ;

/* Variables and functions */
 scalar_t__ DBLENGTH (struct partial_symtab*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  psymtab_to_symtab_1 (struct partial_symtab*) ; 
 int /*<<< orphan*/  scan_file_globals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwarf_psymtab_to_symtab (struct partial_symtab *pst)
{

  if (pst != NULL)
    {
      if (pst->readin)
	{
	  warning ("psymtab for %s already read in.  Shouldn't happen.",
		   pst->filename);
	}
      else
	{
	  if (DBLENGTH (pst) || pst->number_of_dependencies)
	    {
	      /* Print the message now, before starting serious work, to avoid
	         disconcerting pauses.  */
	      if (info_verbose)
		{
		  printf_filtered ("Reading in symbols for %s...",
				   pst->filename);
		  gdb_flush (gdb_stdout);
		}

	      psymtab_to_symtab_1 (pst);

#if 0				/* FIXME:  Check to see what dbxread is doing here and see if
				   we need to do an equivalent or is this something peculiar to
				   stabs/a.out format.
				   Match with global symbols.  This only needs to be done once,
				   after all of the symtabs and dependencies have been read in.
				 */
	      scan_file_globals (pst->objfile);
#endif

	      /* Finish up the verbose info message.  */
	      if (info_verbose)
		{
		  printf_filtered ("done.\n");
		  gdb_flush (gdb_stdout);
		}
	    }
	}
    }
}