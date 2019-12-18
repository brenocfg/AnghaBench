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
struct TYPE_3__ {double* s; } ;
typedef  TYPE_1__ cl_float2 ;

/* Variables and functions */
 double fabs (double) ; 

__attribute__((used)) static bool points_not_collinear(const cl_float2 **points)
{
    int j, k, i = 2;

    for (j = 0; j < i; j++) {
        double dx1 = points[j]->s[0] - points[i]->s[0];
        double dy1 = points[j]->s[1] - points[i]->s[1];

        for (k = 0; k < j; k++) {
            double dx2 = points[k]->s[0] - points[i]->s[0];
            double dy2 = points[k]->s[1] - points[i]->s[1];

            // Assuming a 3840 x 2160 video with a point at (0, 0) and one at
            // (3839, 2159), this prevents a third point from being within roughly
            // 0.5 of a pixel of the line connecting the two on both axes
            if (fabs(dx2*dy1 - dy2*dx1) <= 1.0) {
                return false;
            }
        }
    }

    return true;
}