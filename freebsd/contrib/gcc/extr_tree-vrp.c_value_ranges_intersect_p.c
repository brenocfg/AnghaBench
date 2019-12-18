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
struct TYPE_5__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ value_range_t ;

/* Variables and functions */
 int value_inside_range (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline bool
value_ranges_intersect_p (value_range_t *vr0, value_range_t *vr1)
{
  return (value_inside_range (vr1->min, vr0) == 1
	  || value_inside_range (vr1->max, vr0) == 1
	  || value_inside_range (vr0->min, vr1) == 1
	  || value_inside_range (vr0->max, vr1) == 1);
}