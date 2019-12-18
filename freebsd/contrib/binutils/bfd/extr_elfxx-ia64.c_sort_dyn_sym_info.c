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
struct elfNN_ia64_dyn_sym_info {scalar_t__ addend; scalar_t__ got_offset; } ;
typedef  scalar_t__ bfd_vma ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  addend_compare ; 
 int /*<<< orphan*/  memmove (struct elfNN_ia64_dyn_sym_info*,struct elfNN_ia64_dyn_sym_info*,unsigned int) ; 
 int /*<<< orphan*/  qsort (struct elfNN_ia64_dyn_sym_info*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
sort_dyn_sym_info (struct elfNN_ia64_dyn_sym_info *info,
		   unsigned int count)
{
  bfd_vma curr, prev, got_offset;
  unsigned int i, kept, dup, diff, dest, src, len;

  qsort (info, count, sizeof (*info), addend_compare);

  /* Find the first duplicate.  */
  prev = info [0].addend;
  got_offset = info [0].got_offset;
  for (i = 1; i < count; i++)
    {
      curr = info [i].addend;
      if (curr == prev)
	{
	  /* For duplicates, make sure that GOT_OFFSET is valid.  */
	  if (got_offset == (bfd_vma) -1)
	    got_offset = info [i].got_offset;
	  break;
	}
      got_offset = info [i].got_offset;
      prev = curr;
    }

  /* We may move a block of elements to here.  */
  dest = i++;

  /* Remove duplicates.  */
  if (i < count)
    {
      while (i < count)
	{
	  /* For duplicates, make sure that the kept one has a valid
	     got_offset.  */
	  kept = dest - 1;
	  if (got_offset != (bfd_vma) -1)
	    info [kept].got_offset = got_offset;

	  curr = info [i].addend;
	  got_offset = info [i].got_offset;

	  /* Move a block of elements whose first one is different from
	     the previous.  */
	  if (curr == prev)
	    {
	      for (src = i + 1; src < count; src++)
		{
		  if (info [src].addend != curr)
		    break;
		  /* For duplicates, make sure that GOT_OFFSET is
		     valid.  */
		  if (got_offset == (bfd_vma) -1)
		    got_offset = info [src].got_offset;
		}

	      /* Make sure that the kept one has a valid got_offset.  */
	      if (got_offset != (bfd_vma) -1)
		info [kept].got_offset = got_offset;
	    }
	  else
	    src = i;

	  if (src >= count)
	    break;

	  /* Find the next duplicate.  SRC will be kept.  */
	  prev = info [src].addend;
	  got_offset = info [src].got_offset;
	  for (dup = src + 1; dup < count; dup++)
	    {
	      curr = info [dup].addend;
	      if (curr == prev)
		{
		  /* Make sure that got_offset is valid.  */
		  if (got_offset == (bfd_vma) -1)
		    got_offset = info [dup].got_offset;

		  /* For duplicates, make sure that the kept one has
		     a valid got_offset.  */
		  if (got_offset != (bfd_vma) -1)
		    info [dup - 1].got_offset = got_offset;
		  break;
		}
	      got_offset = info [dup].got_offset;
	      prev = curr;
	    }

	  /* How much to move.  */
	  len = dup - src;
	  i = dup + 1;

	  if (len == 1 && dup < count)
	    {
	      /* If we only move 1 element, we combine it with the next
		 one.  There must be at least a duplicate.  Find the
		 next different one.  */
	      for (diff = dup + 1, src++; diff < count; diff++, src++)
		{
		  if (info [diff].addend != curr)
		    break;
		  /* Make sure that got_offset is valid.  */
		  if (got_offset == (bfd_vma) -1)
		    got_offset = info [diff].got_offset;
		}

	      /* Makre sure that the last duplicated one has an valid
		 offset.  */
	      BFD_ASSERT (curr == prev);
	      if (got_offset != (bfd_vma) -1)
		info [diff - 1].got_offset = got_offset;

	      if (diff < count)
		{
		  /* Find the next duplicate.  Track the current valid
		     offset.  */
		  prev = info [diff].addend;
		  got_offset = info [diff].got_offset;
		  for (dup = diff + 1; dup < count; dup++)
		    {
		      curr = info [dup].addend;
		      if (curr == prev)
			{
			  /* For duplicates, make sure that GOT_OFFSET
			     is valid.  */
			  if (got_offset == (bfd_vma) -1)
			    got_offset = info [dup].got_offset;
			  break;
			}
		      got_offset = info [dup].got_offset;
		      prev = curr;
		      diff++;
		    }

		  len = diff - src + 1;
		  i = diff + 1;
		}
	    }

	  memmove (&info [dest], &info [src], len * sizeof (*info));

	  dest += len;
	}

      count = dest;
    }
  else
    {
      /* When we get here, either there is no duplicate at all or
	 the only duplicate is the last element.  */
      if (dest < count)
	{
	  /* If the last element is a duplicate, make sure that the
	     kept one has a valid got_offset.  We also update count.  */
	  if (got_offset != (bfd_vma) -1)
	    info [dest - 1].got_offset = got_offset;
	  count = dest;
	}
    }

  return count;
}