#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  etree_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_3__ {int /*<<< orphan*/  value; scalar_t__ valid_p; } ;
struct TYPE_4__ {scalar_t__ phase; TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exp_fold_tree_no_dot (int /*<<< orphan*/ *) ; 
 TYPE_2__ expld ; 
 scalar_t__ lang_mark_phase_enum ; 

bfd_vma
exp_get_vma (etree_type *tree, bfd_vma def, char *name)
{
  if (tree != NULL)
    {
      exp_fold_tree_no_dot (tree);
      if (expld.result.valid_p)
	return expld.result.value;
      else if (name != NULL && expld.phase != lang_mark_phase_enum)
	einfo (_("%F%S nonconstant expression for %s\n"), name);
    }
  return def;
}