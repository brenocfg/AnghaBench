#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ _uw ;
struct TYPE_4__ {int /*<<< orphan*/  fnoffset; } ;
typedef  TYPE_1__ const __EIT_entry ;

/* Variables and functions */
 scalar_t__ selfrel_offset31 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const __EIT_entry *
search_EIT_table (const __EIT_entry * table, int nrec, _uw return_address)
{
  _uw next_fn;
  _uw this_fn;
  int n, left, right;

  if (nrec == 0)
    return (__EIT_entry *) 0;

  left = 0;
  right = nrec - 1;

  while (1)
    {
      n = (left + right) / 2;
      this_fn = selfrel_offset31 (&table[n].fnoffset);
      if (n != nrec - 1)
	next_fn = selfrel_offset31 (&table[n + 1].fnoffset) - 1;
      else
	next_fn = (_uw)0 - 1;

      if (return_address < this_fn)
	{
	  if (n == left)
	    return (__EIT_entry *) 0;
	  right = n - 1;
	}
      else if (return_address <= next_fn)
	return &table[n];
      else
	left = n + 1;
    }
}