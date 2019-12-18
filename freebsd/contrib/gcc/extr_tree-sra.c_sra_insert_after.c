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
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 scalar_t__ EXPR_HAS_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPR_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  annotate_all_with_locus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_after (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (TYPE_1__) ; 
 int /*<<< orphan*/  insert_edge_copies (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stmt_ends_bb_p (int /*<<< orphan*/ ) ; 

void
sra_insert_after (block_stmt_iterator *bsi, tree list)
{
  tree stmt = bsi_stmt (*bsi);

  if (EXPR_HAS_LOCATION (stmt))
    annotate_all_with_locus (&list, EXPR_LOCATION (stmt));

  if (stmt_ends_bb_p (stmt))
    insert_edge_copies (list, bsi->bb);
  else
    bsi_insert_after (bsi, list, BSI_SAME_STMT);
}