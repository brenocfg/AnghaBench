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
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* stmt_ann_t ;
typedef  int /*<<< orphan*/ * basic_block ;
struct TYPE_3__ {int /*<<< orphan*/ * bb; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PHI_BB (int /*<<< orphan*/ ) ; 
 scalar_t__ PHI_NODE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* stmt_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline basic_block
bb_for_stmt (tree t)
{
  stmt_ann_t ann;

  if (TREE_CODE (t) == PHI_NODE)
    return PHI_BB (t);

  ann = stmt_ann (t);
  return ann ? ann->bb : NULL;
}