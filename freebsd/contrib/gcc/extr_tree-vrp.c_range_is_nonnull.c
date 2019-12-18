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
 scalar_t__ VR_ANTI_RANGE ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
range_is_nonnull (value_range_t *vr)
{
  return vr->type == VR_ANTI_RANGE
	 && integer_zerop (vr->min)
	 && integer_zerop (vr->max);
}