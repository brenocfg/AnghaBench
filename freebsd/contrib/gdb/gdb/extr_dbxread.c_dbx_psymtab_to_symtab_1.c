#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct partial_symtab {int readin; int number_of_dependencies; TYPE_1__* objfile; struct partial_symtab** dependencies; int /*<<< orphan*/  filename; } ;
struct cleanup {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  obfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_STRING_OFFSET (struct partial_symtab*) ; 
 scalar_t__ LDSYMLEN (struct partial_symtab*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SYMBOL_OFFSET (struct partial_symtab*) ; 
 int /*<<< orphan*/  SYMBOL_SIZE (struct partial_symtab*) ; 
 int /*<<< orphan*/  bfd_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buildsym_init () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  file_string_table_offset ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ info_verbose ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_ofile_symtab (struct partial_symtab*) ; 
 int /*<<< orphan*/  really_free_pendings ; 
 int /*<<< orphan*/  stabsread_init () ; 
 int /*<<< orphan*/  symbol_size ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
dbx_psymtab_to_symtab_1 (struct partial_symtab *pst)
{
  struct cleanup *old_chain;
  int i;

  if (!pst)
    return;

  if (pst->readin)
    {
      fprintf_unfiltered (gdb_stderr, "Psymtab for %s already read in.  Shouldn't happen.\n",
			  pst->filename);
      return;
    }

  /* Read in all partial symtabs on which this one is dependent */
  for (i = 0; i < pst->number_of_dependencies; i++)
    if (!pst->dependencies[i]->readin)
      {
	/* Inform about additional files that need to be read in.  */
	if (info_verbose)
	  {
	    fputs_filtered (" ", gdb_stdout);
	    wrap_here ("");
	    fputs_filtered ("and ", gdb_stdout);
	    wrap_here ("");
	    printf_filtered ("%s...", pst->dependencies[i]->filename);
	    wrap_here ("");	/* Flush output */
	    gdb_flush (gdb_stdout);
	  }
	dbx_psymtab_to_symtab_1 (pst->dependencies[i]);
      }

  if (LDSYMLEN (pst))		/* Otherwise it's a dummy */
    {
      /* Init stuff necessary for reading in symbols */
      stabsread_init ();
      buildsym_init ();
      old_chain = make_cleanup (really_free_pendings, 0);
      file_string_table_offset = FILE_STRING_OFFSET (pst);
      symbol_size = SYMBOL_SIZE (pst);

      /* Read in this file's symbols */
      bfd_seek (pst->objfile->obfd, SYMBOL_OFFSET (pst), SEEK_SET);
      read_ofile_symtab (pst);

      do_cleanups (old_chain);
    }

  pst->readin = 1;
}