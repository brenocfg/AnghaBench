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
struct funcinfo {char* name; struct arange arange; struct funcinfo* prev_func; } ;
struct comp_unit {struct funcinfo* function_table; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
lookup_address_in_function_table (struct comp_unit *unit,
				  bfd_vma addr,
				  struct funcinfo **function_ptr,
				  const char **functionname_ptr)
{
  struct funcinfo* each_func;
  struct funcinfo* best_fit = NULL;
  struct arange *arange;

  for (each_func = unit->function_table;
       each_func;
       each_func = each_func->prev_func)
    {
      for (arange = &each_func->arange;
	   arange;
	   arange = arange->next)
	{
	  if (addr >= arange->low && addr < arange->high)
	    {
	      if (!best_fit ||
		  ((arange->high - arange->low) < (best_fit->arange.high - best_fit->arange.low)))
		best_fit = each_func;
	    }
	}
    }

  if (best_fit)
    {
      *functionname_ptr = best_fit->name;
      *function_ptr = best_fit;
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}