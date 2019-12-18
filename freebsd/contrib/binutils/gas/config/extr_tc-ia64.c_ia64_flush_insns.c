#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; } ;
struct TYPE_11__ {unsigned long slot_number; int /*<<< orphan*/  slot_frag; TYPE_1__ r; struct TYPE_11__* next; } ;
typedef  TYPE_3__ unw_rec_list ;
typedef  int /*<<< orphan*/  subsegT ;
struct label_fix {int dw2_mark_labels; int /*<<< orphan*/  sym; struct label_fix* next; } ;
typedef  int /*<<< orphan*/  segT ;
typedef  int bfd_boolean ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;
struct TYPE_15__ {struct label_fix* tag_fixups; struct label_fix* label_fixups; TYPE_6__ debug_line; } ;
struct TYPE_10__ {scalar_t__ X_op; } ;
struct TYPE_13__ {scalar_t__ num_slots_in_use; TYPE_2__ qp; int /*<<< orphan*/  last_text_seg; } ;
struct TYPE_12__ {TYPE_3__* current_entry; } ;

/* Variables and functions */
 TYPE_8__ CURR_SLOT ; 
 int /*<<< orphan*/  DWARF2_FLAG_BASIC_BLOCK ; 
 int FALSE ; 
 scalar_t__ O_register ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  as_bad (char*) ; 
#define  body 142 
#define  br_gr 141 
#define  copy_state 140 
 int /*<<< orphan*/  dwarf2_gen_line_info (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  dwarf2_where (TYPE_6__*) ; 
 int /*<<< orphan*/  emit_one_bundle () ; 
#define  endp 139 
#define  fr_mem 138 
 scalar_t__ frag_more (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  frag_now_fix () ; 
#define  frgr_mem 137 
#define  gr_gr 136 
#define  gr_mem 135 
#define  label_state 134 
 TYPE_5__ md ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  now_subseg ; 
#define  prologue 133 
#define  prologue_gr 132 
#define  rp_br 131 
#define  spill_base 130 
#define  spill_mask 129 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_set_value_now (int /*<<< orphan*/ ) ; 
#define  unwabi 128 
 TYPE_4__ unwind ; 

void
ia64_flush_insns ()
{
  struct label_fix *lfix;
  segT saved_seg;
  subsegT saved_subseg;
  unw_rec_list *ptr;
  bfd_boolean mark;

  if (!md.last_text_seg)
    return;

  saved_seg = now_seg;
  saved_subseg = now_subseg;

  subseg_set (md.last_text_seg, 0);

  while (md.num_slots_in_use > 0)
    emit_one_bundle ();		/* force out queued instructions */

  /* In case there are labels following the last instruction, resolve
     those now.  */
  mark = FALSE;
  for (lfix = CURR_SLOT.label_fixups; lfix; lfix = lfix->next)
    {
      symbol_set_value_now (lfix->sym);
      mark |= lfix->dw2_mark_labels;
    }
  if (mark)
    {
      dwarf2_where (&CURR_SLOT.debug_line);
      CURR_SLOT.debug_line.flags |= DWARF2_FLAG_BASIC_BLOCK;
      dwarf2_gen_line_info (frag_now_fix (), &CURR_SLOT.debug_line);
    }
  CURR_SLOT.label_fixups = 0;

  for (lfix = CURR_SLOT.tag_fixups; lfix; lfix = lfix->next)
    symbol_set_value_now (lfix->sym);
  CURR_SLOT.tag_fixups = 0;

  /* In case there are unwind directives following the last instruction,
     resolve those now.  We only handle prologue, body, and endp directives
     here.  Give an error for others.  */
  for (ptr = unwind.current_entry; ptr; ptr = ptr->next)
    {
      switch (ptr->r.type)
	{
	case prologue:
	case prologue_gr:
	case body:
	case endp:
	  ptr->slot_number = (unsigned long) frag_more (0);
	  ptr->slot_frag = frag_now;
	  break;

	  /* Allow any record which doesn't have a "t" field (i.e.,
	     doesn't relate to a particular instruction).  */
	case unwabi:
	case br_gr:
	case copy_state:
	case fr_mem:
	case frgr_mem:
	case gr_gr:
	case gr_mem:
	case label_state:
	case rp_br:
	case spill_base:
	case spill_mask:
	  /* nothing */
	  break;

	default:
	  as_bad (_("Unwind directive not followed by an instruction."));
	  break;
	}
    }
  unwind.current_entry = NULL;

  subseg_set (saved_seg, saved_subseg);

  if (md.qp.X_op == O_register)
    as_bad ("qualifying predicate not followed by instruction");
}