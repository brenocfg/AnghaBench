#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rhs; int /*<<< orphan*/  lhs; int /*<<< orphan*/  cond; } ;
struct TYPE_8__ {TYPE_2__ trinary; } ;
typedef  TYPE_3__ etree_type ;
struct TYPE_6__ {scalar_t__ value; scalar_t__ valid_p; } ;
struct TYPE_9__ {TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  exp_fold_tree_1 (int /*<<< orphan*/ ) ; 
 TYPE_5__ expld ; 

__attribute__((used)) static void
fold_trinary (etree_type *tree)
{
  exp_fold_tree_1 (tree->trinary.cond);
  if (expld.result.valid_p)
    exp_fold_tree_1 (expld.result.value
		     ? tree->trinary.lhs
		     : tree->trinary.rhs);
}