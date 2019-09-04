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
 int /*<<< orphan*/  autocorrelation (double const*,int,int,double*,int) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 
 double sqrt (double) ; 

__attribute__((used)) static double autoregression(const double *samples, int ar_order,
                             int nb_samples, double *k, double *r, double *a)
{
    double alpha;
    int i, j;

    memset(a, 0, ar_order * sizeof(*a));

    autocorrelation(samples, ar_order, nb_samples, r, 1. / nb_samples);

    /* Levinson-Durbin algorithm */
    k[0] = a[0] = -r[1] / r[0];
    alpha = r[0] * (1. - k[0] * k[0]);
    for (i = 1; i < ar_order; i++) {
        double epsilon = 0.;

        for (j = 0; j < i; j++)
            epsilon += a[j] * r[i - j];
        epsilon += r[i + 1];

        k[i] = -epsilon / alpha;
        alpha *= (1. - k[i] * k[i]);
        for (j = i - 1; j >= 0; j--)
            k[j] = a[j] + k[i] * a[i - j - 1];
        for (j = 0; j <= i; j++)
            a[j] = k[j];
    }

    k[0] = 1.;
    for (i = 1; i <= ar_order; i++)
        k[i] = a[i - 1];

    return sqrt(alpha);
}