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

/* Variables and functions */
 scalar_t__ PHI_NODE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_stmt_modified (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stmt_operands (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
update_stmt (tree t)
{
  if (TREE_CODE (t) == PHI_NODE)
    return;
  mark_stmt_modified (t);
  update_stmt_operands (t);
}