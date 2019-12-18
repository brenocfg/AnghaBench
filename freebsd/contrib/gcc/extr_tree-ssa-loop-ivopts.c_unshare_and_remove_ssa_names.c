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
 int /*<<< orphan*/  for_each_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idx_remove_ssa_names ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
unshare_and_remove_ssa_names (tree ref)
{
  ref = unshare_expr (ref);
  for_each_index (&ref, idx_remove_ssa_names, NULL);

  return ref;
}