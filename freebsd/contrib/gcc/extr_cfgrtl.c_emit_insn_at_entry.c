#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  edge_iterator ;
typedef  TYPE_1__* edge ;
struct TYPE_6__ {int /*<<< orphan*/  succs; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int EDGE_FALLTHRU ; 
 TYPE_4__* ENTRY_BLOCK_PTR ; 
 int /*<<< orphan*/  commit_edge_insertions () ; 
 TYPE_1__* ei_safe_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  insert_insn_on_edge (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
emit_insn_at_entry (rtx insn)
{
  edge_iterator ei = ei_start (ENTRY_BLOCK_PTR->succs);
  edge e = ei_safe_edge (ei);
  gcc_assert (e->flags & EDGE_FALLTHRU);

  insert_insn_on_edge (insn, e);
  commit_edge_insertions ();
}