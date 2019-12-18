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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ last_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
tree_block_ends_with_condjump_p (basic_block bb)
{
  tree stmt = last_stmt (bb);
  return (stmt && TREE_CODE (stmt) == COND_EXPR);
}