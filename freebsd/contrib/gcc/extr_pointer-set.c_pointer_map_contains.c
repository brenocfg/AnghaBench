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
struct pointer_map_t {size_t n_slots; void** keys; void** values; int /*<<< orphan*/  log_slots; } ;

/* Variables and functions */
 size_t hash1 (void*,size_t,int /*<<< orphan*/ ) ; 

void **
pointer_map_contains (struct pointer_map_t *pmap, void *p)
{
  size_t n = hash1 (p, pmap->n_slots, pmap->log_slots);

  while (true)
    {
      if (pmap->keys[n] == p)
	return &pmap->values[n];
      else if (pmap->keys[n] == 0)
	return NULL;
      else
       {
         ++n;
         if (n == pmap->n_slots)
           n = 0;
       }
    }
}