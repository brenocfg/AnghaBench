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
 float INFINITY ; 

__attribute__((used)) static inline int quant_array_idx(const float val, const float *arr, const int num)
{
    int i, index = 0;
    float quant_min_err = INFINITY;
    for (i = 0; i < num; i++) {
        float error = (val - arr[i])*(val - arr[i]);
        if (error < quant_min_err) {
            quant_min_err = error;
            index = i;
        }
    }
    return index;
}