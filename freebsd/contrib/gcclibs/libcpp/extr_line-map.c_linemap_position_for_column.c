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
struct line_maps {int highest_line; unsigned int max_column_hint; int used; int highest_location; struct line_map* maps; } ;
struct line_map {int dummy; } ;
typedef  int source_location ;

/* Variables and functions */
 int /*<<< orphan*/  SOURCE_LINE (struct line_map*,int) ; 
 int linemap_line_start (struct line_maps*,int /*<<< orphan*/ ,unsigned int) ; 

source_location
linemap_position_for_column (struct line_maps *set, unsigned int to_column)
{
  source_location r = set->highest_line;
  if (to_column >= set->max_column_hint)
    {
      if (r >= 0xC000000 || to_column > 100000)
	{
	  /* Running low on source_locations - disable column numbers.  */
	  return r;
	}
      else
	{
	  struct line_map *map = &set->maps[set->used - 1];
	  r = linemap_line_start (set, SOURCE_LINE (map, r), to_column + 50);
	}
    }
  r = r + to_column;
  if (r >= set->highest_location)
    set->highest_location = r;
  return r;
}