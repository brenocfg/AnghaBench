#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  etree_type ;
struct TYPE_2__ {int /*<<< orphan*/  section; int /*<<< orphan*/ * dotp; scalar_t__ dot; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_abs_section_ptr ; 
 int /*<<< orphan*/  exp_fold_tree_1 (int /*<<< orphan*/ *) ; 
 TYPE_1__ expld ; 

__attribute__((used)) static void
exp_fold_tree_no_dot (etree_type *tree)
{
  expld.dot = 0;
  expld.dotp = NULL;
  expld.section = bfd_abs_section_ptr;
  exp_fold_tree_1 (tree);
}