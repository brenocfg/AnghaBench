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
 int compare_values_warnv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  is_gimple_min_invariant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_values (tree val1, tree val2)
{
  bool sop;
  int ret;

  sop = false;
  ret = compare_values_warnv (val1, val2, &sop);
  if (sop
      && (!is_gimple_min_invariant (val1) || !is_gimple_min_invariant (val2)))
    ret = -2;
  return ret;
}