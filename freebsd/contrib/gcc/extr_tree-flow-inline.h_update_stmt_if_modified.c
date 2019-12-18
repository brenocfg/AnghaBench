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
 scalar_t__ stmt_modified_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stmt_operands (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
update_stmt_if_modified (tree t)
{
  if (stmt_modified_p (t))
    update_stmt_operands (t);
}