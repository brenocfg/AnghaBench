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
struct arange {scalar_t__ high; scalar_t__ low; struct arange* next; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 struct arange* bfd_zalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
arange_add (bfd *abfd, struct arange *first_arange, bfd_vma low_pc, bfd_vma high_pc)
{
  struct arange *arange;

  /* If the first arange is empty, use it. */
  if (first_arange->high == 0)
    {
      first_arange->low = low_pc;
      first_arange->high = high_pc;
      return;
    }

  /* Next see if we can cheaply extend an existing range.  */
  arange = first_arange;
  do
    {
      if (low_pc == arange->high)
	{
	  arange->high = high_pc;
	  return;
	}
      if (high_pc == arange->low)
	{
	  arange->low = low_pc;
	  return;
	}
      arange = arange->next;
    }
  while (arange);

  /* Need to allocate a new arange and insert it into the arange list.
     Order isn't significant, so just insert after the first arange. */
  arange = bfd_zalloc (abfd, sizeof (*arange));
  arange->low = low_pc;
  arange->high = high_pc;
  arange->next = first_arange->next;
  first_arange->next = arange;
}