#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cl_float2 ;
struct TYPE_4__ {int /*<<< orphan*/  const p2; int /*<<< orphan*/  const p1; } ;
struct TYPE_5__ {TYPE_1__ p; } ;
typedef  TYPE_2__ MotionVector ;

/* Variables and functions */
 scalar_t__ points_not_collinear (int /*<<< orphan*/  const**) ; 

__attribute__((used)) static bool check_subset(const MotionVector *pairs_subset)
{
    const cl_float2 *prev_points[] = {
        &pairs_subset[0].p.p1,
        &pairs_subset[1].p.p1,
        &pairs_subset[2].p.p1
    };

    const cl_float2 *curr_points[] = {
        &pairs_subset[0].p.p2,
        &pairs_subset[1].p.p2,
        &pairs_subset[2].p.p2
    };

    return points_not_collinear(prev_points) && points_not_collinear(curr_points);
}