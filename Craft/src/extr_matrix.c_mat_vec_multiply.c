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

void mat_vec_multiply(float *vector, float *a, float *b) {
    float result[4];
    for (int i = 0; i < 4; i++) {
        float total = 0;
        for (int j = 0; j < 4; j++) {
            int p = j * 4 + i;
            int q = j;
            total += a[p] * b[q];
        }
        result[i] = total;
    }
    for (int i = 0; i < 4; i++) {
        vector[i] = result[i];
    }
}