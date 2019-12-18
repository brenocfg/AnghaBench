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
struct comp_unit {struct arange arange; scalar_t__ error; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
comp_unit_contains_address (struct comp_unit *unit, bfd_vma addr)
{
  struct arange *arange;

  if (unit->error)
    return FALSE;

  arange = &unit->arange;
  do
    {
      if (addr >= arange->low && addr < arange->high)
	return TRUE;
      arange = arange->next;
    }
  while (arange);

  return FALSE;
}