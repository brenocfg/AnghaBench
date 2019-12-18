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
struct arange {scalar_t__ low; scalar_t__ high; struct arange* next; } ;
struct funcinfo {char* file; unsigned int line; int /*<<< orphan*/ * sec; struct arange arange; scalar_t__ name; struct funcinfo* prev_func; } ;
struct comp_unit {struct funcinfo* function_table; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static bfd_boolean
lookup_symbol_in_function_table (struct comp_unit *unit,
				 asymbol *sym,
				 bfd_vma addr,
				 const char **filename_ptr,
				 unsigned int *linenumber_ptr)
{
  struct funcinfo* each_func;
  struct funcinfo* best_fit = NULL;
  struct arange *arange;
  const char *name = bfd_asymbol_name (sym);
  asection *sec = bfd_get_section (sym);

  for (each_func = unit->function_table;
       each_func;
       each_func = each_func->prev_func)
    {
      for (arange = &each_func->arange;
	   arange;
	   arange = arange->next)
	{
	  if ((!each_func->sec || each_func->sec == sec)
	      && addr >= arange->low
	      && addr < arange->high
	      && each_func->name
	      && strcmp (name, each_func->name) == 0
	      && (!best_fit
		  || ((arange->high - arange->low)
		      < (best_fit->arange.high - best_fit->arange.low))))
	    best_fit = each_func;
	}
    }

  if (best_fit)
    {
      best_fit->sec = sec;
      *filename_ptr = best_fit->file;
      *linenumber_ptr = best_fit->line;
      return TRUE;
    }
  else
    return FALSE;
}