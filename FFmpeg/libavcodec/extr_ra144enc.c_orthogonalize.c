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
 int BLOCKSIZE ; 

__attribute__((used)) static void orthogonalize(float *v, const float *u)
{
    int i;
    float num = 0, den = 0;

    for (i = 0; i < BLOCKSIZE; i++) {
        num += v[i] * u[i];
        den += u[i] * u[i];
    }
    num /= den;
    for (i = 0; i < BLOCKSIZE; i++)
        v[i] -= num * u[i];
}