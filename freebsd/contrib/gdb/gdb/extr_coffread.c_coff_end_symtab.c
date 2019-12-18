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
struct symtab {int /*<<< orphan*/  filename; } ;
struct objfile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 int /*<<< orphan*/  current_source_end_addr ; 
 int /*<<< orphan*/  current_source_start_addr ; 
 struct symtab* end_symtab (int /*<<< orphan*/ ,struct objfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_named_symtabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * last_source_file ; 
 int /*<<< orphan*/  last_source_start_addr ; 

__attribute__((used)) static void
coff_end_symtab (struct objfile *objfile)
{
  struct symtab *symtab;

  last_source_start_addr = current_source_start_addr;

  symtab = end_symtab (current_source_end_addr, objfile, SECT_OFF_TEXT (objfile));

  if (symtab != NULL)
    free_named_symtabs (symtab->filename);

  /* Reinitialize for beginning of new file. */
  last_source_file = NULL;
}