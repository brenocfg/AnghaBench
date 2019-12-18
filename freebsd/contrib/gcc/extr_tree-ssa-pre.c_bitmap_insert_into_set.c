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
typedef  int tree ;
typedef  TYPE_1__* bitmap_set_t ;
struct TYPE_3__ {int /*<<< orphan*/  expressions; int /*<<< orphan*/  values; } ;

/* Variables and functions */
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int) ; 
 scalar_t__ TREE_CODE (int) ; 
 int /*<<< orphan*/  VALUE_HANDLE_ID (int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int get_value_handle (int) ; 
 int /*<<< orphan*/  is_gimple_min_invariant (int) ; 

__attribute__((used)) static void
bitmap_insert_into_set (bitmap_set_t set, tree expr)
{
  tree val;
  /* XXX: For now, we only let SSA_NAMES into the bitmap sets.  */
  gcc_assert (TREE_CODE (expr) == SSA_NAME);
  val = get_value_handle (expr);

  gcc_assert (val);
  if (!is_gimple_min_invariant (val))
  {
    bitmap_set_bit (set->values, VALUE_HANDLE_ID (val));
    bitmap_set_bit (set->expressions, SSA_NAME_VERSION (expr));
  }
}