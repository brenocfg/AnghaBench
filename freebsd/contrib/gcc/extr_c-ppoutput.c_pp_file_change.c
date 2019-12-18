#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct line_map {scalar_t__ reason; int /*<<< orphan*/  start_location; } ;
struct TYPE_4__ {int /*<<< orphan*/  preprocessed; } ;
struct TYPE_3__ {scalar_t__ first_time; } ;

/* Variables and functions */
 struct line_map* INCLUDED_FROM (int /*<<< orphan*/ *,struct line_map const*) ; 
 int /*<<< orphan*/  LAST_SOURCE_LINE_LOCATION (struct line_map const*) ; 
 scalar_t__ LC_ENTER ; 
 scalar_t__ LC_LEAVE ; 
 TYPE_2__* cpp_get_options (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_no_line_commands ; 
 int /*<<< orphan*/  line_table ; 
 int /*<<< orphan*/  maybe_print_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_in ; 
 TYPE_1__ print ; 
 int /*<<< orphan*/  print_line (int /*<<< orphan*/ ,char const*) ; 

void
pp_file_change (const struct line_map *map)
{
  const char *flags = "";

  if (flag_no_line_commands)
    return;

  if (map != NULL)
    {
      if (print.first_time)
	{
	  /* Avoid printing foo.i when the main file is foo.c.  */
	  if (!cpp_get_options (parse_in)->preprocessed)
	    print_line (map->start_location, flags);
	  print.first_time = 0;
	}
      else
	{
	  /* Bring current file to correct line when entering a new file.  */
	  if (map->reason == LC_ENTER)
	    {
	      const struct line_map *from = INCLUDED_FROM (&line_table, map);
	      maybe_print_line (LAST_SOURCE_LINE_LOCATION (from));
	    }
	  if (map->reason == LC_ENTER)
	    flags = " 1";
	  else if (map->reason == LC_LEAVE)
	    flags = " 2";
	  print_line (map->start_location, flags);
	}
    }
}