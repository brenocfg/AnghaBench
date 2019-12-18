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
struct ui_stream {int /*<<< orphan*/  stream; } ;
struct ui_out {int dummy; } ;
struct symtab {TYPE_1__* linetable; } ;
struct linetable_entry {int dummy; } ;
struct disassemble_info {int dummy; } ;
struct cleanup {int dummy; } ;
struct TYPE_2__ {int nitems; struct linetable_entry* item; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  do_assembly_only (struct ui_out*,struct disassemble_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ui_stream*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_mixed_source_and_assembly (struct ui_out*,struct disassemble_info*,int,struct linetable_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symtab*,int,struct ui_stream*) ; 
 struct symtab* find_pc_symtab (int /*<<< orphan*/ ) ; 
 struct disassemble_info gdb_disassemble_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct cleanup* make_cleanup_ui_out_stream_delete (struct ui_stream*) ; 
 struct ui_stream* ui_out_stream_new (struct ui_out*) ; 

void
gdb_disassembly (struct ui_out *uiout,
		char *file_string,
		int line_num,
		int mixed_source_and_assembly,
		int how_many, CORE_ADDR low, CORE_ADDR high)
{
  struct ui_stream *stb = ui_out_stream_new (uiout);
  struct cleanup *cleanups = make_cleanup_ui_out_stream_delete (stb);
  struct disassemble_info di = gdb_disassemble_info (current_gdbarch, stb->stream);
  /* To collect the instruction outputted from opcodes. */
  struct symtab *symtab = NULL;
  struct linetable_entry *le = NULL;
  int nlines = -1;

  /* Assume symtab is valid for whole PC range */
  symtab = find_pc_symtab (low);

  if (symtab != NULL && symtab->linetable != NULL)
    {
      /* Convert the linetable to a bunch of my_line_entry's.  */
      le = symtab->linetable->item;
      nlines = symtab->linetable->nitems;
    }

  if (!mixed_source_and_assembly || nlines <= 0
      || symtab == NULL || symtab->linetable == NULL)
    do_assembly_only (uiout, &di, low, high, how_many, stb);

  else if (mixed_source_and_assembly)
    do_mixed_source_and_assembly (uiout, &di, nlines, le, low,
				  high, symtab, how_many, stb);

  do_cleanups (cleanups);
  gdb_flush (gdb_stdout);
}