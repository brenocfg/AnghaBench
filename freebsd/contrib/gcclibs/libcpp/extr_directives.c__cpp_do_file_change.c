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
struct line_map {int /*<<< orphan*/  to_line; } ;
typedef  enum lc_reason { ____Placeholder_lc_reason } lc_reason ;
struct TYPE_5__ {int /*<<< orphan*/  (* file_change ) (TYPE_2__*,struct line_map const*) ;} ;
struct TYPE_6__ {TYPE_1__ cb; int /*<<< orphan*/  line_table; } ;
typedef  TYPE_2__ cpp_reader ;

/* Variables and functions */
 struct line_map* linemap_add (int /*<<< orphan*/ ,int,unsigned int,char const*,unsigned int) ; 
 int /*<<< orphan*/  linemap_line_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct line_map const*) ; 

void
_cpp_do_file_change (cpp_reader *pfile, enum lc_reason reason,
		     const char *to_file, unsigned int file_line,
		     unsigned int sysp)
{
  const struct line_map *map = linemap_add (pfile->line_table, reason, sysp,
					    to_file, file_line);
  if (map != NULL)
    linemap_line_start (pfile->line_table, map->to_line, 127);

  if (pfile->cb.file_change)
    pfile->cb.file_change (pfile, map);
}