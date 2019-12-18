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
struct TYPE_3__ {double const** coeff; } ;
typedef  TYPE_1__ LLSModel ;

/* Variables and functions */

__attribute__((used)) static double evaluate_lls(LLSModel *m, const double *param, int order)
{
    int i;
    double out = 0;

    for (i = 0; i <= order; i++)
        out += param[i] * m->coeff[order][i];

    return out;
}