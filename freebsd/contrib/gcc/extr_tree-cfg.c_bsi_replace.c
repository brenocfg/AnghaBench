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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {int /*<<< orphan*/  bb; } ;
typedef  TYPE_1__ block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_LOCUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EXPR_LOCUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_stmt_to_eh_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bsi_stmt (TYPE_1__ const) ; 
 int /*<<< orphan*/ * bsi_stmt_ptr (TYPE_1__ const) ; 
 int /*<<< orphan*/  delink_stmt_imm_use (int /*<<< orphan*/ ) ; 
 int lookup_stmt_eh_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_stmt_modified (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_stmt_from_eh_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bb_for_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_modified_stmts (int /*<<< orphan*/ ) ; 

void
bsi_replace (const block_stmt_iterator *bsi, tree stmt, bool update_eh_info)
{
  int eh_region;
  tree orig_stmt = bsi_stmt (*bsi);

  SET_EXPR_LOCUS (stmt, EXPR_LOCUS (orig_stmt));
  set_bb_for_stmt (stmt, bsi->bb);

  /* Preserve EH region information from the original statement, if
     requested by the caller.  */
  if (update_eh_info)
    {
      eh_region = lookup_stmt_eh_region (orig_stmt);
      if (eh_region >= 0)
	{
	  remove_stmt_from_eh_region (orig_stmt);
	  add_stmt_to_eh_region (stmt, eh_region);
	}
    }

  delink_stmt_imm_use (orig_stmt);
  *bsi_stmt_ptr (*bsi) = stmt;
  mark_stmt_modified (stmt);
  update_modified_stmts (stmt);
}