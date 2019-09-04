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

void frustum_planes(float planes[6][4], int radius, float *matrix) {
    float znear = 0.125;
    float zfar = radius * 32 + 64;
    float *m = matrix;
    planes[0][0] = m[3] + m[0];
    planes[0][1] = m[7] + m[4];
    planes[0][2] = m[11] + m[8];
    planes[0][3] = m[15] + m[12];
    planes[1][0] = m[3] - m[0];
    planes[1][1] = m[7] - m[4];
    planes[1][2] = m[11] - m[8];
    planes[1][3] = m[15] - m[12];
    planes[2][0] = m[3] + m[1];
    planes[2][1] = m[7] + m[5];
    planes[2][2] = m[11] + m[9];
    planes[2][3] = m[15] + m[13];
    planes[3][0] = m[3] - m[1];
    planes[3][1] = m[7] - m[5];
    planes[3][2] = m[11] - m[9];
    planes[3][3] = m[15] - m[13];
    planes[4][0] = znear * m[3] + m[2];
    planes[4][1] = znear * m[7] + m[6];
    planes[4][2] = znear * m[11] + m[10];
    planes[4][3] = znear * m[15] + m[14];
    planes[5][0] = zfar * m[3] - m[2];
    planes[5][1] = zfar * m[7] - m[6];
    planes[5][2] = zfar * m[11] - m[10];
    planes[5][3] = zfar * m[15] - m[14];
}