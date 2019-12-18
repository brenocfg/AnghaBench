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
 double trunc (double) ; 

__attribute__((used)) static void fwht_1d(double *out, const double *in, int sz)
{
    double t0 = in[0] + in[1];
    double t3 = in[3] - in[2];
    double t4 = trunc((t0 - t3) * 0.5);
    double t1 = t4 - in[1];
    double t2 = t4 - in[2];

    out[0] = t0 - t2;
    out[1] = t2;
    out[2] = t3 + t1;
    out[3] = t1;
}