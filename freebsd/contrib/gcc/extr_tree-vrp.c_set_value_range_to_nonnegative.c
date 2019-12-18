#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  equiv; } ;
typedef  TYPE_1__ value_range_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_RANGE ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  positive_overflow_infinity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range_to_varying (TYPE_1__*) ; 
 int /*<<< orphan*/  supports_overflow_infinity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_value_range_to_nonnegative (value_range_t *vr, tree type,
				bool overflow_infinity)
{
  tree zero;

  if (overflow_infinity && !supports_overflow_infinity (type))
    {
      set_value_range_to_varying (vr);
      return;
    }

  zero = build_int_cst (type, 0);
  set_value_range (vr, VR_RANGE, zero,
		   (overflow_infinity
		    ? positive_overflow_infinity (type)
		    : TYPE_MAX_VALUE (type)),
		   vr->equiv);
}