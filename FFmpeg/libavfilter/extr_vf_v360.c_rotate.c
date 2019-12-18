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

__attribute__((used)) static inline void rotate(const float rot_mat[3][3],
                          float *vec)
{
    const float x_tmp = vec[0] * rot_mat[0][0] + vec[1] * rot_mat[0][1] + vec[2] * rot_mat[0][2];
    const float y_tmp = vec[0] * rot_mat[1][0] + vec[1] * rot_mat[1][1] + vec[2] * rot_mat[1][2];
    const float z_tmp = vec[0] * rot_mat[2][0] + vec[1] * rot_mat[2][1] + vec[2] * rot_mat[2][2];

    vec[0] = x_tmp;
    vec[1] = y_tmp;
    vec[2] = z_tmp;
}