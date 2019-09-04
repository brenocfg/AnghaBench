#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* coeff; } ;
typedef  TYPE_1__ SwsVector ;

/* Variables and functions */
 int M_PI ; 
 int exp (double) ; 
 int sqrt (int) ; 
 TYPE_1__* sws_allocVec (int const) ; 
 int /*<<< orphan*/  sws_normalizeVec (TYPE_1__*,double) ; 

SwsVector *sws_getGaussianVec(double variance, double quality)
{
    const int length = (int)(variance * quality + 0.5) | 1;
    int i;
    double middle  = (length - 1) * 0.5;
    SwsVector *vec;

    if(variance < 0 || quality < 0)
        return NULL;

    vec = sws_allocVec(length);

    if (!vec)
        return NULL;

    for (i = 0; i < length; i++) {
        double dist = i - middle;
        vec->coeff[i] = exp(-dist * dist / (2 * variance * variance)) /
                        sqrt(2 * variance * M_PI);
    }

    sws_normalizeVec(vec, 1.0);

    return vec;
}