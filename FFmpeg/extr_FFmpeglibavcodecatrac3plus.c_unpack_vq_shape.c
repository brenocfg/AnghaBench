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
typedef  int int8_t ;

/* Variables and functions */
 int* atrac3p_qu_num_to_seg ; 

__attribute__((used)) static inline void unpack_vq_shape(int start_val, const int8_t *shape_vec,
                                   int *dst, int num_values)
{
    int i;

    if (num_values) {
        dst[0] = dst[1] = dst[2] = start_val;
        for (i = 3; i < num_values; i++)
            dst[i] = start_val - shape_vec[atrac3p_qu_num_to_seg[i] - 1];
    }
}