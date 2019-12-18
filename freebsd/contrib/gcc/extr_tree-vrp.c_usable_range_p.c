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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ value_range_t ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_UNDEFINED (int /*<<< orphan*/ ) ; 
 scalar_t__ VR_RANGE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ is_overflow_infinity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
usable_range_p (value_range_t *vr, bool *strict_overflow_p)
{
  gcc_assert (vr->type == VR_RANGE);
  if (is_overflow_infinity (vr->min))
    {
      *strict_overflow_p = true;
      if (!TYPE_OVERFLOW_UNDEFINED (TREE_TYPE (vr->min)))
	return false;
    }
  if (is_overflow_infinity (vr->max))
    {
      *strict_overflow_p = true;
      if (!TYPE_OVERFLOW_UNDEFINED (TREE_TYPE (vr->max)))
	return false;
    }
  return true;
}