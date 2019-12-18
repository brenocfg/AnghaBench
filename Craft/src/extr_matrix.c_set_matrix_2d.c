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
 int /*<<< orphan*/  mat_ortho (float*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 

void set_matrix_2d(float *matrix, int width, int height) {
    mat_ortho(matrix, 0, width, 0, height, -1, 1);
}