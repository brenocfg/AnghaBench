#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int /*<<< orphan*/  tsi; } ;
typedef  TYPE_1__ block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  bsi_stmt (TYPE_1__) ; 
 int /*<<< orphan*/  delink_stmt_imm_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_stmt_modified (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_stmt_from_eh_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bb_for_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_delink (int /*<<< orphan*/ *) ; 

void
bsi_remove (block_stmt_iterator *i, bool remove_eh_info)
{
  tree t = bsi_stmt (*i);
  set_bb_for_stmt (t, NULL);
  delink_stmt_imm_use (t);
  tsi_delink (&i->tsi);
  mark_stmt_modified (t);
  if (remove_eh_info)
    remove_stmt_from_eh_region (t);
}