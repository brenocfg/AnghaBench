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
 int /*<<< orphan*/  MultiplyMatrix (double,double,double,double*,double*,double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB2YUV_matrix ; 

void Colours_RGB2YUV(double r, double g, double b, double *y, double *u, double *v)
{
	MultiplyMatrix(r, g, b, y, u, v, RGB2YUV_matrix);
}