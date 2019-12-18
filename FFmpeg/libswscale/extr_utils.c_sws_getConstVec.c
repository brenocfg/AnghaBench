#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double* coeff; } ;
typedef  TYPE_1__ SwsVector ;

/* Variables and functions */
 TYPE_1__* sws_allocVec (int) ; 

SwsVector *sws_getConstVec(double c, int length)
{
    int i;
    SwsVector *vec = sws_allocVec(length);

    if (!vec)
        return NULL;

    for (i = 0; i < length; i++)
        vec->coeff[i] = c;

    return vec;
}