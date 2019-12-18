#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  container; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ tree_stmt_iterator ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  STATEMENT_LIST_TAIL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree_stmt_iterator
tsi_last (tree t)
{
  tree_stmt_iterator i;

  i.ptr = STATEMENT_LIST_TAIL (t);
  i.container = t;

  return i;
}