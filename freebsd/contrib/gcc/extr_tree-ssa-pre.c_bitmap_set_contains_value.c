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
struct TYPE_3__ {int /*<<< orphan*/  values; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_HANDLE_ID (int /*<<< orphan*/ ) ; 
 int bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bitmap_set_contains_value (bitmap_set_t set, tree val)
{
  if (is_gimple_min_invariant (val))
    return true;
  return bitmap_bit_p (set->values, VALUE_HANDLE_ID (val));
}