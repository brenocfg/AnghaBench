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
struct pointer_map_t {size_t n_slots; void** keys; void** values; } ;

/* Variables and functions */

void pointer_map_traverse (struct pointer_map_t *pmap,
			   bool (*fn) (void *, void **, void *), void *data)
{
  size_t i;
  for (i = 0; i < pmap->n_slots; ++i)
    if (pmap->keys[i] && !fn (pmap->keys[i], &pmap->values[i], data))
      break;
}