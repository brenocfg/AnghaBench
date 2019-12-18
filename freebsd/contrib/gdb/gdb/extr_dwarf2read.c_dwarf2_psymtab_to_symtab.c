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
struct partial_symtab {int /*<<< orphan*/  filename; scalar_t__ readin; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  psymtab_to_symtab_1 (struct partial_symtab*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwarf2_psymtab_to_symtab (struct partial_symtab *pst)
{
  /* FIXME: This is barely more than a stub.  */
  if (pst != NULL)
    {
      if (pst->readin)
	{
	  warning ("bug: psymtab for %s is already read in.", pst->filename);
	}
      else
	{
	  if (info_verbose)
	    {
	      printf_filtered ("Reading in symbols for %s...", pst->filename);
	      gdb_flush (gdb_stdout);
	    }

	  psymtab_to_symtab_1 (pst);

	  /* Finish up the debug error message.  */
	  if (info_verbose)
	    printf_filtered ("done.\n");
	}
    }
}