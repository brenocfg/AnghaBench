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
struct dwarf2_line_info {int /*<<< orphan*/  isa; int /*<<< orphan*/  flags; scalar_t__ column; int /*<<< orphan*/  filenum; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 scalar_t__ DEBUG_DWARF2 ; 
 int /*<<< orphan*/  DWARF2_FLAG_IS_STMT ; 
 int /*<<< orphan*/  as_where (char**,int /*<<< orphan*/ *) ; 
 struct dwarf2_line_info current ; 
 scalar_t__ debug_type ; 
 int /*<<< orphan*/  get_filenum (char*,int /*<<< orphan*/ ) ; 

void
dwarf2_where (struct dwarf2_line_info *line)
{
  if (debug_type == DEBUG_DWARF2)
    {
      char *filename;
      as_where (&filename, &line->line);
      line->filenum = get_filenum (filename, 0);
      line->column = 0;
      line->flags = DWARF2_FLAG_IS_STMT;
      line->isa = current.isa;
    }
  else
    *line = current;
}