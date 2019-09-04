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
 float acos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axpy_cpu (int,float,float*,int,float*,int) ; 
 int /*<<< orphan*/  dot_cpu (int,float*,int,float*,int) ; 
 int /*<<< orphan*/  fill_cpu (int,int /*<<< orphan*/ ,float*,int) ; 
 float mag_array (float*,int) ; 
 int /*<<< orphan*/  scale_array (float*,int,int) ; 
 float sin (float) ; 

void slerp(float *start, float *end, float s, int n, float *out)
{
    float omega = acos(dot_cpu(n, start, 1, end, 1));
    float so = sin(omega);
    fill_cpu(n, 0, out, 1);
    axpy_cpu(n, sin((1-s)*omega)/so, start, 1, out, 1);
    axpy_cpu(n, sin(s*omega)/so, end, 1, out, 1);

    float mag = mag_array(out, n);
    scale_array(out, n, 1./mag);
}