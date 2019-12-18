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
struct TYPE_3__ {double count; double decay; double coeff; } ;
typedef  TYPE_1__ Predictor ;

/* Variables and functions */

__attribute__((used)) static void update_predictor(Predictor *p, double q, double var, double size)
{
    double new_coeff = size * q / (var + 1);
    if (var < 10)
        return;

    p->count *= p->decay;
    p->coeff *= p->decay;
    p->count++;
    p->coeff += new_coeff;
}