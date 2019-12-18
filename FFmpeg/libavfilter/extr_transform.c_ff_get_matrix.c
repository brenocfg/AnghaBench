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
 float cos (float) ; 
 float sin (float) ; 

void ff_get_matrix(
    float x_shift,
    float y_shift,
    float angle,
    float scale_x,
    float scale_y,
    float *matrix
) {
    matrix[0] = scale_x * cos(angle);
    matrix[1] = -sin(angle);
    matrix[2] = x_shift;
    matrix[3] = -matrix[1];
    matrix[4] = scale_y * cos(angle);
    matrix[5] = y_shift;
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 1;
}