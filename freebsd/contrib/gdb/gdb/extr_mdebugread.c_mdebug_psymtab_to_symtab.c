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
struct partial_symtab {int /*<<< orphan*/  objfile; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  mdebug_next_symbol_text ; 
 int /*<<< orphan*/  next_symbol_text_func ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  psymtab_to_symtab_1 (struct partial_symtab*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_file_globals (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mdebug_psymtab_to_symtab (struct partial_symtab *pst)
{

  if (!pst)
    return;

  if (info_verbose)
    {
      printf_filtered ("Reading in symbols for %s...", pst->filename);
      gdb_flush (gdb_stdout);
    }

  next_symbol_text_func = mdebug_next_symbol_text;

  psymtab_to_symtab_1 (pst, pst->filename);

  /* Match with global symbols.  This only needs to be done once,
     after all of the symtabs and dependencies have been read in.   */
  scan_file_globals (pst->objfile);

  if (info_verbose)
    printf_filtered ("done.\n");
}