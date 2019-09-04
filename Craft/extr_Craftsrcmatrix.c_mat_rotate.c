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
 float cosf (float) ; 
 int /*<<< orphan*/  normalize (float*,float*,float*) ; 
 float sinf (float) ; 

void mat_rotate(float *matrix, float x, float y, float z, float angle) {
    normalize(&x, &y, &z);
    float s = sinf(angle);
    float c = cosf(angle);
    float m = 1 - c;
    matrix[0] = m * x * x + c;
    matrix[1] = m * x * y - z * s;
    matrix[2] = m * z * x + y * s;
    matrix[3] = 0;
    matrix[4] = m * x * y + z * s;
    matrix[5] = m * y * y + c;
    matrix[6] = m * y * z - x * s;
    matrix[7] = 0;
    matrix[8] = m * z * x - y * s;
    matrix[9] = m * y * z + x * s;
    matrix[10] = m * z * z + c;
    matrix[11] = 0;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}