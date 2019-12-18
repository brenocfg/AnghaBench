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
struct ieee_range {scalar_t__ low; scalar_t__ high; struct ieee_range* next; } ;
struct ieee_handle {struct ieee_range* ranges; struct ieee_range* global_ranges; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  free (struct ieee_range*) ; 
 int /*<<< orphan*/  memset (struct ieee_range*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
ieee_add_range (struct ieee_handle *info, bfd_boolean global, bfd_vma low,
		bfd_vma high)
{
  struct ieee_range **plist, *r, **pr;

  if (low == (bfd_vma) -1 || high == (bfd_vma) -1 || low == high)
    return TRUE;

  if (global)
    plist = &info->global_ranges;
  else
    plist = &info->ranges;

  for (r = *plist; r != NULL; r = r->next)
    {
      if (high >= r->low && low <= r->high)
	{
	  /* The new range overlaps r.  */
	  if (low < r->low)
	    r->low = low;
	  if (high > r->high)
	    r->high = high;
	  pr = &r->next;
	  while (*pr != NULL && (*pr)->low <= r->high)
	    {
	      struct ieee_range *n;

	      if ((*pr)->high > r->high)
		r->high = (*pr)->high;
	      n = (*pr)->next;
	      free (*pr);
	      *pr = n;
	    }
	  return TRUE;
	}
    }

  r = (struct ieee_range *) xmalloc (sizeof *r);
  memset (r, 0, sizeof *r);

  r->low = low;
  r->high = high;

  /* Store the ranges sorted by address.  */
  for (pr = plist; *pr != NULL; pr = &(*pr)->next)
    if ((*pr)->low > high)
      break;
  r->next = *pr;
  *pr = r;

  return TRUE;
}