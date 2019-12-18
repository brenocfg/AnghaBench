#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct line_maps {int used; int /*<<< orphan*/  highest_line; struct line_map* maps; } ;
struct line_map {int /*<<< orphan*/  to_file; } ;
struct TYPE_6__ {struct line_maps* line_table; TYPE_1__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_5__ {int sysp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_RENAME ; 
 int /*<<< orphan*/  SOURCE_LINE (struct line_map const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cpp_do_file_change (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
cpp_make_system_header (cpp_reader *pfile, int syshdr, int externc)
{
  int flags = 0;
  const struct line_maps *line_table = pfile->line_table;
  const struct line_map *map = &line_table->maps[line_table->used-1];

  /* 1 = system header, 2 = system header to be treated as C.  */
  if (syshdr)
    flags = 1 + (externc != 0);
  pfile->buffer->sysp = flags;
  _cpp_do_file_change (pfile, LC_RENAME, map->to_file,
		       SOURCE_LINE (map, pfile->line_table->highest_line), flags);
}