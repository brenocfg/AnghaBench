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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 

void
bsi_move_before (block_stmt_iterator *from, block_stmt_iterator *to)
{
  tree stmt = bsi_stmt (*from);
  bsi_remove (from, false);
  bsi_insert_before (to, stmt, BSI_SAME_STMT);
}