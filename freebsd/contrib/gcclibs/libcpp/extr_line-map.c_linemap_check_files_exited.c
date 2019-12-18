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
struct line_maps {int used; struct line_map* maps; } ;
struct line_map {char* to_file; } ;

/* Variables and functions */
 struct line_map* INCLUDED_FROM (struct line_maps*,struct line_map*) ; 
 int /*<<< orphan*/  MAIN_FILE_P (struct line_map*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
linemap_check_files_exited (struct line_maps *set)
{
  struct line_map *map;
  /* Depending upon whether we are handling preprocessed input or
     not, this can be a user error or an ICE.  */
  for (map = &set->maps[set->used - 1]; ! MAIN_FILE_P (map);
       map = INCLUDED_FROM (set, map))
    fprintf (stderr, "line-map.c: file \"%s\" entered but not left\n",
	     map->to_file);
}