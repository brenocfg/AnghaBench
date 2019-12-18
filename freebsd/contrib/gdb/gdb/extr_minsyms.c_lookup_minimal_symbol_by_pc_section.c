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
struct objfile {int minimal_symbol_count; struct minimal_symbol* msymbols; struct objfile* next; } ;
struct obj_section {int dummy; } ;
struct minimal_symbol {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  asection ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/ * SYMBOL_BFD_SECTION (struct minimal_symbol*) ; 
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 struct obj_section* find_pc_section (scalar_t__) ; 
 scalar_t__ mst_abs ; 
 struct objfile* object_files ; 

struct minimal_symbol *
lookup_minimal_symbol_by_pc_section (CORE_ADDR pc, asection *section)
{
  int lo;
  int hi;
  int new;
  struct objfile *objfile;
  struct minimal_symbol *msymbol;
  struct minimal_symbol *best_symbol = NULL;
  struct obj_section *pc_section;

  /* PC has to be in a known section.  This ensures that anything
     beyond the end of the last segment doesn't appear to be part of
     the last function in the last segment.  */
  pc_section = find_pc_section (pc);
  if (pc_section == NULL)
    return NULL;

  /* NOTE: cagney/2004-01-27: Removed code (added 2003-07-19) that was
     trying to force the PC into a valid section as returned by
     find_pc_section.  It broke IRIX 6.5 mdebug which relies on this
     code returning an absolute symbol - the problem was that
     find_pc_section wasn't returning an absolute section and hence
     the code below would skip over absolute symbols.  Since the
     original problem was with finding a frame's function, and that
     uses [indirectly] lookup_minimal_symbol_by_pc, the original
     problem has been fixed by having that function use
     find_pc_section.  */

  for (objfile = object_files;
       objfile != NULL;
       objfile = objfile->next)
    {
      /* If this objfile has a minimal symbol table, go search it using
         a binary search.  Note that a minimal symbol table always consists
         of at least two symbols, a "real" symbol and the terminating
         "null symbol".  If there are no real symbols, then there is no
         minimal symbol table at all. */

      if (objfile->minimal_symbol_count > 0)
	{
          msymbol = objfile->msymbols;
	  lo = 0;
	  hi = objfile->minimal_symbol_count - 1;

	  /* This code assumes that the minimal symbols are sorted by
	     ascending address values.  If the pc value is greater than or
	     equal to the first symbol's address, then some symbol in this
	     minimal symbol table is a suitable candidate for being the
	     "best" symbol.  This includes the last real symbol, for cases
	     where the pc value is larger than any address in this vector.

	     By iterating until the address associated with the current
	     hi index (the endpoint of the test interval) is less than
	     or equal to the desired pc value, we accomplish two things:
	     (1) the case where the pc value is larger than any minimal
	     symbol address is trivially solved, (2) the address associated
	     with the hi index is always the one we want when the interation
	     terminates.  In essence, we are iterating the test interval
	     down until the pc value is pushed out of it from the high end.

	     Warning: this code is trickier than it would appear at first. */

	  /* Should also require that pc is <= end of objfile.  FIXME! */
	  if (pc >= SYMBOL_VALUE_ADDRESS (&msymbol[lo]))
	    {
	      while (SYMBOL_VALUE_ADDRESS (&msymbol[hi]) > pc)
		{
		  /* pc is still strictly less than highest address */
		  /* Note "new" will always be >= lo */
		  new = (lo + hi) / 2;
		  if ((SYMBOL_VALUE_ADDRESS (&msymbol[new]) >= pc) ||
		      (lo == new))
		    {
		      hi = new;
		    }
		  else
		    {
		      lo = new;
		    }
		}

	      /* If we have multiple symbols at the same address, we want
	         hi to point to the last one.  That way we can find the
	         right symbol if it has an index greater than hi.  */
	      while (hi < objfile->minimal_symbol_count - 1
		     && (SYMBOL_VALUE_ADDRESS (&msymbol[hi])
			 == SYMBOL_VALUE_ADDRESS (&msymbol[hi + 1])))
		hi++;

	      /* The minimal symbol indexed by hi now is the best one in this
	         objfile's minimal symbol table.  See if it is the best one
	         overall. */

	      /* Skip any absolute symbols.  This is apparently what adb
	         and dbx do, and is needed for the CM-5.  There are two
	         known possible problems: (1) on ELF, apparently end, edata,
	         etc. are absolute.  Not sure ignoring them here is a big
	         deal, but if we want to use them, the fix would go in
	         elfread.c.  (2) I think shared library entry points on the
	         NeXT are absolute.  If we want special handling for this
	         it probably should be triggered by a special
	         mst_abs_or_lib or some such.  */
	      while (hi >= 0
		     && msymbol[hi].type == mst_abs)
		--hi;

	      /* If "section" specified, skip any symbol from wrong section */
	      /* This is the new code that distinguishes it from the old function */
	      if (section)
		while (hi >= 0
		       /* Some types of debug info, such as COFF,
			  don't fill the bfd_section member, so don't
			  throw away symbols on those platforms.  */
		       && SYMBOL_BFD_SECTION (&msymbol[hi]) != NULL
		       && SYMBOL_BFD_SECTION (&msymbol[hi]) != section)
		  --hi;

	      if (hi >= 0
		  && ((best_symbol == NULL) ||
		      (SYMBOL_VALUE_ADDRESS (best_symbol) <
		       SYMBOL_VALUE_ADDRESS (&msymbol[hi]))))
		{
		  best_symbol = &msymbol[hi];
		}
	    }
	}
    }
  return (best_symbol);
}