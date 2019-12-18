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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int BLOCK_NUM (scalar_t__) ; 
 scalar_t__ CALL_P (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  alloc_INSN_LIST (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blocks_with_calls ; 
 int /*<<< orphan*/  canon_list_insert ; 
 int /*<<< orphan*/ * canon_modify_mem_list ; 
 int /*<<< orphan*/ * modify_mem_list ; 
 int /*<<< orphan*/  modify_mem_list_set ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
record_last_mem_set_info (rtx insn)
{
  int bb = BLOCK_NUM (insn);

  /* load_killed_in_block_p will handle the case of calls clobbering
     everything.  */
  modify_mem_list[bb] = alloc_INSN_LIST (insn, modify_mem_list[bb]);
  bitmap_set_bit (modify_mem_list_set, bb);

  if (CALL_P (insn))
    {
      /* Note that traversals of this loop (other than for free-ing)
	 will break after encountering a CALL_INSN.  So, there's no
	 need to insert a pair of items, as canon_list_insert does.  */
      canon_modify_mem_list[bb] =
	alloc_INSN_LIST (insn, canon_modify_mem_list[bb]);
      bitmap_set_bit (blocks_with_calls, bb);
    }
  else
    note_stores (PATTERN (insn), canon_list_insert, (void*) insn);
}