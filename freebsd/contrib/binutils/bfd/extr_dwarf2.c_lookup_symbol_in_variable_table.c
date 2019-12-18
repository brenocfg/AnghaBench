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
struct varinfo {scalar_t__ stack; char* file; scalar_t__ addr; unsigned int line; int /*<<< orphan*/ * sec; int /*<<< orphan*/ * name; struct varinfo* prev_var; } ;
struct comp_unit {struct varinfo* variable_table; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
lookup_symbol_in_variable_table (struct comp_unit *unit,
				 asymbol *sym,
				 bfd_vma addr,
				 const char **filename_ptr,
				 unsigned int *linenumber_ptr)
{
  const char *name = bfd_asymbol_name (sym);
  asection *sec = bfd_get_section (sym);
  struct varinfo* each;

  for (each = unit->variable_table; each; each = each->prev_var)
    if (each->stack == 0
	&& each->file != NULL
	&& each->name != NULL
	&& each->addr == addr
	&& (!each->sec || each->sec == sec)
	&& strcmp (name, each->name) == 0)
      break;

  if (each)
    {
      each->sec = sec;
      *filename_ptr = each->file;
      *linenumber_ptr = each->line;
      return TRUE;
    }
  else
    return FALSE;
}