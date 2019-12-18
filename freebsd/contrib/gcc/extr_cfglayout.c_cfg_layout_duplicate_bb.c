#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* rtx ;
typedef  TYPE_3__* basic_block ;
struct TYPE_15__ {int /*<<< orphan*/  prev_bb; } ;
struct TYPE_13__ {TYPE_1__* rtl; } ;
struct TYPE_14__ {TYPE_2__ il; } ;
struct TYPE_12__ {void* global_live_at_end; void* global_live_at_start; void* footer; void* header; } ;

/* Variables and functions */
 void* ALLOC_REG_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BB_COPY_PARTITION (TYPE_3__*,TYPE_3__*) ; 
 void* BB_END (TYPE_3__*) ; 
 void* BB_HEAD (TYPE_3__*) ; 
 int /*<<< orphan*/  COPY_REG_SET (void*,void*) ; 
 TYPE_7__* EXIT_BLOCK_PTR ; 
 void* NEXT_INSN (void*) ; 
 TYPE_3__* create_basic_block (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* duplicate_insn_chain (void*,void*) ; 
 int /*<<< orphan*/ * get_last_insn () ; 
 int /*<<< orphan*/  reg_obstack ; 
 void* unlink_insn_chain (void*,int /*<<< orphan*/ *) ; 

basic_block
cfg_layout_duplicate_bb (basic_block bb)
{
  rtx insn;
  basic_block new_bb;

  insn = duplicate_insn_chain (BB_HEAD (bb), BB_END (bb));
  new_bb = create_basic_block (insn,
			       insn ? get_last_insn () : NULL,
			       EXIT_BLOCK_PTR->prev_bb);

  BB_COPY_PARTITION (new_bb, bb);
  if (bb->il.rtl->header)
    {
      insn = bb->il.rtl->header;
      while (NEXT_INSN (insn))
	insn = NEXT_INSN (insn);
      insn = duplicate_insn_chain (bb->il.rtl->header, insn);
      if (insn)
	new_bb->il.rtl->header = unlink_insn_chain (insn, get_last_insn ());
    }

  if (bb->il.rtl->footer)
    {
      insn = bb->il.rtl->footer;
      while (NEXT_INSN (insn))
	insn = NEXT_INSN (insn);
      insn = duplicate_insn_chain (bb->il.rtl->footer, insn);
      if (insn)
	new_bb->il.rtl->footer = unlink_insn_chain (insn, get_last_insn ());
    }

  if (bb->il.rtl->global_live_at_start)
    {
      new_bb->il.rtl->global_live_at_start = ALLOC_REG_SET (&reg_obstack);
      new_bb->il.rtl->global_live_at_end = ALLOC_REG_SET (&reg_obstack);
      COPY_REG_SET (new_bb->il.rtl->global_live_at_start,
		    bb->il.rtl->global_live_at_start);
      COPY_REG_SET (new_bb->il.rtl->global_live_at_end,
		    bb->il.rtl->global_live_at_end);
    }

  return new_bb;
}