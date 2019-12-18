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
struct line_maps {unsigned int cache; unsigned int used; struct line_map const* maps; } ;
typedef  struct line_map {scalar_t__ start_location; } const line_map ;
typedef  scalar_t__ source_location ;

/* Variables and functions */

const struct line_map *
linemap_lookup (struct line_maps *set, source_location line)
{
  unsigned int md, mn, mx;
  const struct line_map *cached;

  mn = set->cache;
  mx = set->used;
  
  cached = &set->maps[mn];
  /* We should get a segfault if no line_maps have been added yet.  */
  if (line >= cached->start_location)
    {
      if (mn + 1 == mx || line < cached[1].start_location)
	return cached;
    }
  else
    {
      mx = mn;
      mn = 0;
    }

  while (mx - mn > 1)
    {
      md = (mn + mx) / 2;
      if (set->maps[md].start_location > line)
	mx = md;
      else
	mn = md;
    }

  set->cache = mn;
  return &set->maps[mn];
}