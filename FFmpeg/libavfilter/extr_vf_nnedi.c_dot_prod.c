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
struct TYPE_5__ {TYPE_1__* fdsp; } ;
struct TYPE_4__ {float (* scalarproduct_float ) (float const*,float const*,int const) ;} ;
typedef  TYPE_2__ NNEDIContext ;

/* Variables and functions */
 float stub1 (float const*,float const*,int const) ; 

__attribute__((used)) static void dot_prod(NNEDIContext *s, const float *data, const float *weights, float *vals, const int n, const int len, const float *scale)
{
    int i;

    for (i = 0; i < n; i++) {
        float sum;

        sum = s->fdsp->scalarproduct_float(data, &weights[i * len], len);

        vals[i] = sum * scale[0] + weights[n * len + i];
    }
}