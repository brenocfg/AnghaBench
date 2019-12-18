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
struct symbol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  main_func_highpc; int /*<<< orphan*/  main_func_lowpc; } ;
struct objfile {TYPE_1__ ei; int /*<<< orphan*/  section_offsets; int /*<<< orphan*/ * obfd; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLOCK_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLOCK_START (int /*<<< orphan*/ ) ; 
 scalar_t__ LOC_BLOCK ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  init_minimal_symbol_collection () ; 
 int /*<<< orphan*/  install_minimal_symbols (struct objfile*) ; 
 struct symbol* lookup_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_name () ; 
 struct cleanup* make_cleanup_discard_minimal_symbols () ; 
 int /*<<< orphan*/  nlm_symtab_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct objfile*) ; 
 int /*<<< orphan*/  stabsect_build_psymtabs (struct objfile*,int,char*,char*,char*) ; 

__attribute__((used)) static void
nlm_symfile_read (struct objfile *objfile, int mainline)
{
  bfd *abfd = objfile->obfd;
  struct cleanup *back_to;
  CORE_ADDR offset;
  struct symbol *mainsym;

  init_minimal_symbol_collection ();
  back_to = make_cleanup_discard_minimal_symbols ();

  /* FIXME, should take a section_offsets param, not just an offset.  */

  offset = ANOFFSET (objfile->section_offsets, 0);

  /* Process the NLM export records, which become the bfd's canonical symbol
     table. */

  nlm_symtab_read (abfd, offset, objfile);

  /* Install any minimal symbols that have been collected as the current
     minimal symbols for this objfile. */

  install_minimal_symbols (objfile);
  do_cleanups (back_to);

  stabsect_build_psymtabs (objfile, mainline, ".stab",
			   ".stabstr", ".text");

  mainsym = lookup_symbol (main_name (), NULL, VAR_DOMAIN, NULL, NULL);

  if (mainsym
      && SYMBOL_CLASS (mainsym) == LOC_BLOCK)
    {
      objfile->ei.main_func_lowpc = BLOCK_START (SYMBOL_BLOCK_VALUE (mainsym));
      objfile->ei.main_func_highpc = BLOCK_END (SYMBOL_BLOCK_VALUE (mainsym));
    }

  /* FIXME:  We could locate and read the optional native debugging format
     here and add the symbols to the minimal symbol table. */
}