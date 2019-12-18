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
typedef  int /*<<< orphan*/  value_set_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  get_value_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_into_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_contains_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
value_insert_into_set (value_set_t set, tree expr)
{
  tree val = get_value_handle (expr);

  /* Constant and invariant values exist everywhere, and thus,
     actually keeping them in the sets is pointless.  */
  if (is_gimple_min_invariant (val))
    return;

  if (!set_contains_value (set, val))
    insert_into_set (set, expr);
}