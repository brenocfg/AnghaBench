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
 int /*<<< orphan*/  VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_local_temp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_target_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
force_target_expr (tree type, tree init)
{
  tree slot;

  gcc_assert (!VOID_TYPE_P (type));

  slot = build_local_temp (type);
  return build_target_expr (slot, init);
}