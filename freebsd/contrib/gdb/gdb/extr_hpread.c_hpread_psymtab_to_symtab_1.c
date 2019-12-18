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
struct partial_symtab {int readin; int number_of_dependencies; int /*<<< orphan*/  filename; int /*<<< orphan*/  section_offsets; scalar_t__ textlow; scalar_t__ texthigh; int /*<<< orphan*/  objfile; int /*<<< orphan*/  symtab; struct partial_symtab** dependencies; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 scalar_t__ LDSYMLEN (struct partial_symtab*) ; 
 int /*<<< orphan*/  LDSYMOFF (struct partial_symtab*) ; 
 int /*<<< orphan*/  buildsym_init () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  hpread_expand_symtab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ info_verbose ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  really_free_pendings ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
hpread_psymtab_to_symtab_1 (struct partial_symtab *pst)
{
  struct cleanup *old_chain;
  int i;

  /* Get out quick if passed junk.  */
  if (!pst)
    return;

  /* Complain if we've already read in this symbol table.  */
  if (pst->readin)
    {
      fprintf_unfiltered (gdb_stderr, "Psymtab for %s already read in."
			  "  Shouldn't happen.\n",
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
	hpread_psymtab_to_symtab_1 (pst->dependencies[i]);
      }

  /* If it's real...  */
  if (LDSYMLEN (pst))
    {
      /* Init stuff necessary for reading in symbols */
      buildsym_init ();
      old_chain = make_cleanup (really_free_pendings, 0);

      pst->symtab =
	hpread_expand_symtab (pst->objfile, LDSYMOFF (pst), LDSYMLEN (pst),
			      pst->textlow, pst->texthigh - pst->textlow,
			      pst->section_offsets, pst->filename);

      do_cleanups (old_chain);
    }

  pst->readin = 1;
}