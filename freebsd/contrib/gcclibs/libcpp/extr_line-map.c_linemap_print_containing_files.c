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
struct line_maps {scalar_t__ last_listed; } ;
struct line_map {scalar_t__ included_from; char* to_file; } ;

/* Variables and functions */
 struct line_map* INCLUDED_FROM (struct line_maps*,struct line_map const*) ; 
 int LAST_SOURCE_LINE (struct line_map const*) ; 
 scalar_t__ MAIN_FILE_P (struct line_map const*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
linemap_print_containing_files (struct line_maps *set,
				const struct line_map *map)
{
  if (MAIN_FILE_P (map) || set->last_listed == map->included_from)
    return;

  set->last_listed = map->included_from;
  map = INCLUDED_FROM (set, map);

  fprintf (stderr,  _("In file included from %s:%u"),
	   map->to_file, LAST_SOURCE_LINE (map));

  while (! MAIN_FILE_P (map))
    {
      map = INCLUDED_FROM (set, map);
      /* Translators note: this message is used in conjunction
	 with "In file included from %s:%ld" and some other
	 tricks.  We want something like this:

	 | In file included from sys/select.h:123,
	 |                  from sys/types.h:234,
	 |                  from userfile.c:31:
	 | bits/select.h:45: <error message here>

	 with all the "from"s lined up.
	 The trailing comma is at the beginning of this message,
	 and the trailing colon is not translated.  */
      fprintf (stderr, _(",\n                 from %s:%u"),
	       map->to_file, LAST_SOURCE_LINE (map));
    }

  fputs (":\n", stderr);
}