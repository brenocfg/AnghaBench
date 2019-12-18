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
struct ui_stream {int /*<<< orphan*/  stream; } ;
struct ui_out {int dummy; } ;
struct disassemble_info {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
 scalar_t__ TARGET_PRINT_INSN (scalar_t__,struct disassemble_info*) ; 
 int /*<<< orphan*/  build_address_symbolic (scalar_t__,int /*<<< orphan*/ ,char**,int*,char**,int*,int*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (struct ui_out*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_file_rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_core_addr (struct ui_out*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ui_out_field_int (struct ui_out*,char*,int) ; 
 int /*<<< orphan*/  ui_out_field_stream (struct ui_out*,char*,struct ui_stream*) ; 
 int /*<<< orphan*/  ui_out_field_string (struct ui_out*,char*,char*) ; 
 int /*<<< orphan*/  ui_out_text (struct ui_out*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static int
dump_insns (struct ui_out *uiout, struct disassemble_info * di,
	    CORE_ADDR low, CORE_ADDR high,
	    int how_many, struct ui_stream *stb)
{
  int num_displayed = 0;
  CORE_ADDR pc;

  /* parts of the symbolic representation of the address */
  int unmapped;
  int offset;
  int line;
  struct cleanup *ui_out_chain;

  for (pc = low; pc < high;)
    {
      char *filename = NULL;
      char *name = NULL;

      QUIT;
      if (how_many >= 0)
	{
	  if (num_displayed >= how_many)
	    break;
	  else
	    num_displayed++;
	}
      ui_out_chain = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
      ui_out_field_core_addr (uiout, "address", pc);

      if (!build_address_symbolic (pc, 0, &name, &offset, &filename,
				   &line, &unmapped))
	{
	  /* We don't care now about line, filename and
	     unmapped. But we might in the future. */
	  ui_out_text (uiout, " <");
	  ui_out_field_string (uiout, "func-name", name);
	  ui_out_text (uiout, "+");
	  ui_out_field_int (uiout, "offset", offset);
	  ui_out_text (uiout, ">:\t");
	}
      else
	ui_out_text (uiout, ":\t");

      if (filename != NULL)
	xfree (filename);
      if (name != NULL)
	xfree (name);

      ui_file_rewind (stb->stream);
      pc += TARGET_PRINT_INSN (pc, di);
      ui_out_field_stream (uiout, "inst", stb);
      ui_file_rewind (stb->stream);
      do_cleanups (ui_out_chain);
      ui_out_text (uiout, "\n");
    }
  return num_displayed;
}