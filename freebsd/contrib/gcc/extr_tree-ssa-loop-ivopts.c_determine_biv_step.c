#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct loop {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  step; } ;
typedef  TYPE_1__ affine_iv ;
struct TYPE_5__ {struct loop* loop_father; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PHI_RESULT (int /*<<< orphan*/ ) ; 
 TYPE_3__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_iv (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ zero_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
determine_biv_step (tree phi)
{
  struct loop *loop = bb_for_stmt (phi)->loop_father;
  tree name = PHI_RESULT (phi);
  affine_iv iv;

  if (!is_gimple_reg (name))
    return NULL_TREE;

  if (!simple_iv (loop, phi, name, &iv, true))
    return NULL_TREE;

  return (zero_p (iv.step) ? NULL_TREE : iv.step);
}