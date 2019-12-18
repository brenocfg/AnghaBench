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
struct deps {int pending_flush_length; int /*<<< orphan*/  last_pending_memory_flush; scalar_t__ pending_lists_length; int /*<<< orphan*/  pending_write_mems; int /*<<< orphan*/  pending_write_insns; int /*<<< orphan*/  pending_read_mems; int /*<<< orphan*/  pending_read_insns; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  REG_DEP_ANTI ; 
 int /*<<< orphan*/  REG_DEP_OUTPUT ; 
 int /*<<< orphan*/  add_dependence_list_and_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_INSN_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_EXPR_LIST_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
flush_pending_lists (struct deps *deps, rtx insn, int for_read,
		     int for_write)
{
  if (for_write)
    {
      add_dependence_list_and_free (insn, &deps->pending_read_insns, 1,
				    REG_DEP_ANTI);
      free_EXPR_LIST_list (&deps->pending_read_mems);
    }

  add_dependence_list_and_free (insn, &deps->pending_write_insns, 1,
				for_read ? REG_DEP_ANTI : REG_DEP_OUTPUT);
  free_EXPR_LIST_list (&deps->pending_write_mems);
  deps->pending_lists_length = 0;

  add_dependence_list_and_free (insn, &deps->last_pending_memory_flush, 1,
				for_read ? REG_DEP_ANTI : REG_DEP_OUTPUT);
  deps->last_pending_memory_flush = alloc_INSN_LIST (insn, NULL_RTX);
  deps->pending_flush_length = 1;
}