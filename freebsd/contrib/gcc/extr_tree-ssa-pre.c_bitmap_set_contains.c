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
typedef  TYPE_1__* bitmap_set_t ;
struct TYPE_3__ {int /*<<< orphan*/  expressions; } ;

/* Variables and functions */
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_value_handle (int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bitmap_set_contains (bitmap_set_t set, tree expr)
{
  /* All constants are in every set.  */
  if (is_gimple_min_invariant (get_value_handle (expr)))
    return true;

  /* XXX: Bitmapped sets only contain SSA_NAME's for now.  */
  if (TREE_CODE (expr) != SSA_NAME)
    return false;
  return bitmap_bit_p (set->expressions, SSA_NAME_VERSION (expr));
}