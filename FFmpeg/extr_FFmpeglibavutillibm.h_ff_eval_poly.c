#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static inline double ff_eval_poly(const double *coeff, int size, double x) {
    double sum = coeff[size-1];
    int i;
    for (i = size-2; i >= 0; --i) {
        sum *= x;
        sum += coeff[i];
    }
    return sum;
}