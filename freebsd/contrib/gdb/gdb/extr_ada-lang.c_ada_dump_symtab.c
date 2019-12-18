#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symtab {char* dirname; char* filename; char* debugformat; int block_line_section; TYPE_1__* linetable; } ;
struct linetable_entry {scalar_t__ pc; scalar_t__ line; } ;
struct TYPE_2__ {int nitems; struct linetable_entry* item; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void
ada_dump_symtab (struct symtab *s)
{
  int i;
  fprintf (stderr, "New symtab: [\n");
  fprintf (stderr, "  Name: %s/%s;\n",
	   s->dirname ? s->dirname : "?", s->filename ? s->filename : "?");
  fprintf (stderr, "  Format: %s;\n", s->debugformat);
  if (s->linetable != NULL)
    {
      fprintf (stderr, "  Line table (section %d):\n", s->block_line_section);
      for (i = 0; i < s->linetable->nitems; i += 1)
	{
	  struct linetable_entry *e = s->linetable->item + i;
	  fprintf (stderr, "    %4ld: %8lx\n", (long) e->line, (long) e->pc);
	}
    }
  fprintf (stderr, "]\n");
}