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
typedef  int int16_t ;
typedef  int /*<<< orphan*/  NNEDIContext ;

/* Variables and functions */

__attribute__((used)) static void dot_prods(NNEDIContext *s, const float *dataf, const float *weightsf, float *vals, const int n, const int len, const float *scale)
{
    const int16_t *data = (int16_t *)dataf;
    const int16_t *weights = (int16_t *)weightsf;
    const float *wf = (float *)&weights[n * len];
    int i, j;

    for (i = 0; i < n; i++) {
        int sum = 0, off = ((i >> 2) << 3) + (i & 3);
        for (j = 0; j < len; j++)
            sum += data[j] * weights[i * len + j];

        vals[i] = sum * wf[off] * scale[0] + wf[off + 4];
    }
}