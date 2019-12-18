#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {int index; } ;

/* Variables and functions */
 scalar_t__ BB_END (TYPE_1__*) ; 
 scalar_t__ BB_HEAD (TYPE_1__*) ; 
 int /*<<< orphan*/  LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NOTE_INSN_BASIC_BLOCK ; 
 scalar_t__ NOTE_LINE_NUMBER (scalar_t__) ; 
 int /*<<< orphan*/  NOTE_P (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ dump_file ; 
 scalar_t__ emit_insn_after_noloc (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  print_inline_rtx (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void
insert_insn_start_bb (rtx insn, basic_block bb)
{
  /* Insert at start of successor block.  */
  rtx prev = PREV_INSN (BB_HEAD (bb));
  rtx before = BB_HEAD (bb);
  while (before != 0)
    {
      if (! LABEL_P (before)
	  && (! NOTE_P (before)
	      || NOTE_LINE_NUMBER (before) != NOTE_INSN_BASIC_BLOCK))
	break;
      prev = before;
      if (prev == BB_END (bb))
	break;
      before = NEXT_INSN (before);
    }

  insn = emit_insn_after_noloc (insn, prev);

  if (dump_file)
    {
      fprintf (dump_file, "STORE_MOTION  insert store at start of BB %d:\n",
	       bb->index);
      print_inline_rtx (dump_file, insn, 6);
      fprintf (dump_file, "\n");
    }
}