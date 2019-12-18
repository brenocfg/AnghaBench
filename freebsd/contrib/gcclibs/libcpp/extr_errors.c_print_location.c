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
struct line_map {char* to_file; } ;
typedef  scalar_t__ source_location ;
struct TYPE_4__ {int /*<<< orphan*/  line_table; } ;
typedef  TYPE_1__ cpp_reader ;

/* Variables and functions */
 scalar_t__ CPP_OPTION (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int SOURCE_COLUMN (struct line_map const*,scalar_t__) ; 
 unsigned int SOURCE_LINE (struct line_map const*,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 struct line_map* linemap_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  linemap_print_containing_files (int /*<<< orphan*/ ,struct line_map const*) ; 
 char* progname ; 
 int /*<<< orphan*/  show_column ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_location (cpp_reader *pfile, source_location line, unsigned int col)
{
  if (line == 0)
    fprintf (stderr, "%s: ", progname);
  else
    {
      const struct line_map *map;
      unsigned int lin;

      map = linemap_lookup (pfile->line_table, line);
      linemap_print_containing_files (pfile->line_table, map);

      lin = SOURCE_LINE (map, line);
      if (col == 0)
	{
	  col = SOURCE_COLUMN (map, line);
	  if (col == 0)
	    col = 1;
	}

      if (lin == 0)
	fprintf (stderr, "%s:", map->to_file);
      else if (CPP_OPTION (pfile, show_column) == 0)
	fprintf (stderr, "%s:%u:", map->to_file, lin);
      else
	fprintf (stderr, "%s:%u:%u:", map->to_file, lin, col);

      fputc (' ', stderr);
    }
}