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
struct line_info_table {struct line_info* last_line; } ;
struct line_info {scalar_t__ address; char* filename; unsigned int line; struct line_info* prev_line; int /*<<< orphan*/  end_sequence; } ;
struct arange {scalar_t__ low; struct arange* next; } ;
struct funcinfo {struct arange arange; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static bfd_boolean
lookup_address_in_line_info_table (struct line_info_table *table,
				   bfd_vma addr,
				   struct funcinfo *function,
				   const char **filename_ptr,
				   unsigned int *linenumber_ptr)
{
  /* Note: table->last_line should be a descendingly sorted list. */
  struct line_info* next_line = table->last_line;
  struct line_info* each_line = NULL;
  *filename_ptr = NULL;

  if (!next_line)
    return FALSE;

  each_line = next_line->prev_line;

  /* Check for large addresses */
  if (addr > next_line->address)
    each_line = NULL; /* ensure we skip over the normal case */

  /* Normal case: search the list; save  */
  while (each_line && next_line)
    {
      /* If we have an address match, save this info.  This allows us
	 to return as good as results as possible for strange debugging
	 info.  */
      bfd_boolean addr_match = FALSE;
      if (each_line->address <= addr && addr < next_line->address)
	{
	  addr_match = TRUE;

	  /* If this line appears to span functions, and addr is in the
	     later function, return the first line of that function instead
	     of the last line of the earlier one.  This check is for GCC
	     2.95, which emits the first line number for a function late.  */

	  if (function != NULL)
	    {
	      bfd_vma lowest_pc;
	      struct arange *arange;

	      /* Find the lowest address in the function's range list */
	      lowest_pc = function->arange.low;
	      for (arange = &function->arange;
		   arange;
		   arange = arange->next)
		{
		  if (function->arange.low < lowest_pc)
		    lowest_pc = function->arange.low;
		}
	      /* Check for spanning function and set outgoing line info */
	      if (addr >= lowest_pc
		  && each_line->address < lowest_pc
		  && next_line->address > lowest_pc)
		{
		  *filename_ptr = next_line->filename;
		  *linenumber_ptr = next_line->line;
		}
	      else
		{
		  *filename_ptr = each_line->filename;
		  *linenumber_ptr = each_line->line;
		}
	    }
	  else
	    {
	      *filename_ptr = each_line->filename;
	      *linenumber_ptr = each_line->line;
	    }
	}

      if (addr_match && !each_line->end_sequence)
	return TRUE; /* we have definitely found what we want */

      next_line = each_line;
      each_line = each_line->prev_line;
    }

  /* At this point each_line is NULL but next_line is not.  If we found
     a candidate end-of-sequence point in the loop above, we can return
     that (compatibility with a bug in the Intel compiler); otherwise,
     assuming that we found the containing function for this address in
     this compilation unit, return the first line we have a number for
     (compatibility with GCC 2.95).  */
  if (*filename_ptr == NULL && function != NULL)
    {
      *filename_ptr = next_line->filename;
      *linenumber_ptr = next_line->line;
      return TRUE;
    }

  return FALSE;
}