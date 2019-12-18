#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double* s; } ;
typedef  TYPE_2__ cl_float2 ;
struct TYPE_5__ {TYPE_2__ p2; TYPE_2__ p1; } ;
struct TYPE_7__ {TYPE_1__ p; } ;
typedef  TYPE_3__ MotionVector ;

/* Variables and functions */

__attribute__((used)) static void compute_error(
    const MotionVector *point_pairs,
    const int num_point_pairs,
    const double *model,
    float *err
) {
    double F0 = model[0], F1 = model[1], F2 = model[2];
    double F3 = model[3], F4 = model[4], F5 = model[5];

    for (int i = 0; i < num_point_pairs; i++) {
        const cl_float2 *f = &point_pairs[i].p.p1;
        const cl_float2 *t = &point_pairs[i].p.p2;

        double a = F0*f->s[0] + F1*f->s[1] + F2 - t->s[0];
        double b = F3*f->s[0] + F4*f->s[1] + F5 - t->s[1];

        err[i] = a*a + b*b;
    }
}