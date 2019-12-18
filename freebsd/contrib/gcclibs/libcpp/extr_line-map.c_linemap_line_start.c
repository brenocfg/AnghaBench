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
struct line_maps {int used; int highest_location; int highest_line; unsigned int max_column_hint; struct line_map* maps; } ;
struct line_map {int column_bits; unsigned int to_line; int start_location; int /*<<< orphan*/  to_file; int /*<<< orphan*/  sysp; } ;
typedef  int source_location ;

/* Variables and functions */
 int /*<<< orphan*/  LC_RENAME ; 
 int SOURCE_COLUMN (struct line_map*,int) ; 
 unsigned int SOURCE_LINE (struct line_map*,int) ; 
 scalar_t__ linemap_add (struct line_maps*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

source_location
linemap_line_start (struct line_maps *set, unsigned int to_line,
		    unsigned int max_column_hint)
{
  struct line_map *map = &set->maps[set->used - 1];
  source_location highest = set->highest_location;
  source_location r;
  unsigned int last_line = SOURCE_LINE (map, set->highest_line);
  int line_delta = to_line - last_line;
  bool add_map = false;
  if (line_delta < 0
      || (line_delta > 10 && line_delta * map->column_bits > 1000)
      || (max_column_hint >= (1U << map->column_bits))
      || (max_column_hint <= 80 && map->column_bits >= 10))
    {
      add_map = true;
    }
  else
    max_column_hint = set->max_column_hint;
  if (add_map)
    {
      int column_bits;
      if (max_column_hint > 100000 || highest > 0xC0000000)
	{
	  /* If the column number is ridiculous or we've allocated a huge
	     number of source_locations, give up on column numbers. */
	  max_column_hint = 0;
	  if (highest >0xF0000000)
	    return 0;
	  column_bits = 0;
	}
      else
	{
	  column_bits = 7;
	  while (max_column_hint >= (1U << column_bits))
	    column_bits++;
	  max_column_hint = 1U << column_bits;
	}
      /* Allocate the new line_map.  However, if the current map only has a
	 single line we can sometimes just increase its column_bits instead. */
      if (line_delta < 0
	  || last_line != map->to_line
	  || SOURCE_COLUMN (map, highest) >= (1U << column_bits))
	map = (struct line_map*) linemap_add (set, LC_RENAME, map->sysp,
				      map->to_file, to_line);
      map->column_bits = column_bits;
      r = map->start_location + ((to_line - map->to_line) << column_bits);
    }
  else
    r = highest - SOURCE_COLUMN (map, highest)
      + (line_delta << map->column_bits);
  set->highest_line = r;
  if (r > set->highest_location)
    set->highest_location = r;
  set->max_column_hint = max_column_hint;
  return r;
}