#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
struct TYPE_6__ {scalar_t__ value; TYPE_1__* section; } ;
typedef  TYPE_2__ asymbol ;
struct TYPE_5__ {scalar_t__ vma; int id; } ;

/* Variables and functions */

__attribute__((used)) static asymbol *
sym_exists_at (asymbol **syms, long lo, long hi, int id, bfd_vma value)
{
  long mid;

  if (id == -1)
    {
      while (lo < hi)
	{
	  mid = (lo + hi) >> 1;
	  if (syms[mid]->value + syms[mid]->section->vma < value)
	    lo = mid + 1;
	  else if (syms[mid]->value + syms[mid]->section->vma > value)
	    hi = mid;
	  else
	    return syms[mid];
	}
    }
  else
    {
      while (lo < hi)
	{
	  mid = (lo + hi) >> 1;
	  if (syms[mid]->section->id < id)
	    lo = mid + 1;
	  else if (syms[mid]->section->id > id)
	    hi = mid;
	  else if (syms[mid]->value < value)
	    lo = mid + 1;
	  else if (syms[mid]->value > value)
	    hi = mid;
	  else
	    return syms[mid];
	}
    }
  return NULL;
}