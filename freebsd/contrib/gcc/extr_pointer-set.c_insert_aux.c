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

/* Variables and functions */
 size_t hash1 (void*,size_t,size_t) ; 

__attribute__((used)) static inline size_t
insert_aux (void *p, void **slots, size_t n_slots, size_t log_slots)
{
  size_t n = hash1 (p, n_slots, log_slots);
  while (true)
    {
      if (slots[n] == p || slots[n] == 0)
	return n;
      else
	{
	  ++n;
	  if (n == n_slots)
	    n = 0;
	}
    }
}