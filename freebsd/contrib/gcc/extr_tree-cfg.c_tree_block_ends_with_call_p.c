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
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_call_expr_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
tree_block_ends_with_call_p (basic_block bb)
{
  block_stmt_iterator bsi = bsi_last (bb);
  return get_call_expr_in (bsi_stmt (bsi)) != NULL;
}