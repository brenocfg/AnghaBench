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
 float FFMAX (double,double) ; 
 int LP_ORDER ; 

__attribute__((used)) static float stability_factor(const float *isf, const float *isf_past)
{
    int i;
    float acc = 0.0;

    for (i = 0; i < LP_ORDER - 1; i++)
        acc += (isf[i] - isf_past[i]) * (isf[i] - isf_past[i]);

    // XXX: This part is not so clear from the reference code
    // the result is more accurate changing the "/ 256" to "* 512"
    return FFMAX(0.0, 1.25 - acc * 0.8 * 512);
}