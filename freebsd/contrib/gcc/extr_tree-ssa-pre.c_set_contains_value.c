#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_set_t ;
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 int value_exists_in_set_bitmap (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
set_contains_value (value_set_t set, tree val)
{
  /* All constants are in every set.  */
  if (is_gimple_min_invariant (val))
    return true;

  if (!set || set->length == 0)
    return false;

  return value_exists_in_set_bitmap (set, val);
}