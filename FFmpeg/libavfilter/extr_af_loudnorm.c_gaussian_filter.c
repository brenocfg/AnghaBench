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
struct TYPE_3__ {double* delta; double* weights; } ;
typedef  TYPE_1__ LoudNormContext ;

/* Variables and functions */

__attribute__((used)) static double gaussian_filter(LoudNormContext *s, int index)
{
    double result = 0.;
    int i;

    index = index - 10 > 0 ? index - 10 : index + 20;
    for (i = 0; i < 21; i++)
        result += s->delta[((index + i) < 30) ? (index + i) : (index + i - 30)] * s->weights[i];

    return result;
}