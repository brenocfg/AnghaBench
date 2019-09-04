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
typedef  double uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dequant_lsps(double *lsps, int num,
                         const uint16_t *values,
                         const uint16_t *sizes,
                         int n_stages, const uint8_t *table,
                         const double *mul_q,
                         const double *base_q)
{
    int n, m;

    memset(lsps, 0, num * sizeof(*lsps));
    for (n = 0; n < n_stages; n++) {
        const uint8_t *t_off = &table[values[n] * num];
        double base = base_q[n], mul = mul_q[n];

        for (m = 0; m < num; m++)
            lsps[m] += base + mul * t_off[m];

        table += sizes[n] * num;
    }
}